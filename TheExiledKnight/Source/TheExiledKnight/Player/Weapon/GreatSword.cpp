// Made by Somalia Pirate


#include "GreatSword.h"

AGreatSword::AGreatSword()
{
	PrimaryActorTick.bCanEverTick = true;

	GreatSword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GreatSword"));
	RootComponent = GreatSword;

	ConstructorHelpers::FObjectFinder<UStaticMesh> GreatSwordMeshFinder(TEXT("/AssetShare/Animations/GreatSword/GreatSword/Weapon/GreatSword_01"));
	if (GreatSwordMeshFinder.Succeeded())
	{
		GreatSwordMesh = GreatSwordMeshFinder.Object;
	}
	GreatSword->SetStaticMesh(GreatSwordMesh);

	WeaponCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	WeaponCapsuleComponent->SetupAttachment(RootComponent);
	WeaponCapsuleComponent->SetRelativeLocationAndRotation(FVector(60, 0, 0), FRotator(-90, 0, 0));
	WeaponCapsuleComponent->SetRelativeScale3D(FVector(1.f, 1.f, 3.f));

	MaxAttackCombo = 3;

	WeaponAdditionalDamage = 20;
}

void AGreatSword::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGreatSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGreatSword::PlayWeaponEquipAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (EKPlayer && EKPlayerController)
	{
		if (!EKPlayerController->bIsEquipWeapon && GreatSwordEquipAnim)
		{
			EKPlayer->PlayAnimMontage(GreatSwordEquipAnim);
		}
		else if (EKPlayerController->bIsEquipWeapon && GreatSwordUnEquipAnim)
		{
			EKPlayer->PlayAnimMontage(GreatSwordUnEquipAnim);
		}
	}
}

void AGreatSword::PlayAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !GreatSwordAttackAnim)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < GreatSwordAttackStamina)
	{
		return;
	}

	if (AttackCombo == 1)
	{
		EKPlayer->StopAnimMontage(GreatSwordAttackAnim);
		EKPlayer->PlayAnimMontage(GreatSwordAttackAnim, 1.0f, FName("Attack1"));
		EKPlayerController->SetAttackEndTimer(2.27f);
	}
	else if (AttackCombo == 2)
	{
		EKPlayer->StopAnimMontage(GreatSwordAttackAnim);
		EKPlayer->PlayAnimMontage(GreatSwordAttackAnim, 1.0f, FName("Attack2"));
		EKPlayerController->SetAttackEndTimer(2.37f);
	}
	else if (AttackCombo == 3)
	{
		EKPlayer->StopAnimMontage(GreatSwordAttackAnim);
		EKPlayer->PlayAnimMontage(GreatSwordAttackAnim, 1.0f, FName("Attack3"));
		EKPlayerController->SetAttackEndTimer(2.7f);
	}

	EKPlayerController->SetStaminaAndTimer(GreatSwordAttackStamina);
}

void AGreatSword::PlayEnhancedAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !GreatSwordEnhancedAttackAnim)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < GreatSwordEnhancedAttackStamina)
	{
		return;
	}

	/*if (EKPlayer->GetPlayerStatusComponent()->GetGreatSwordEnhancedCombo() == 1)
	{
		EKPlayer->PlayAnimMontage(GreatSwordEnhancedAttackAnim, 1.f, FName("Attack1"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetGreatSwordEnhancedCombo() == 2)
	{
		EKPlayer->PlayAnimMontage(GreatSwordEnhancedAttackAnim, 1.f, FName("Attack2"));
	}*/

	EKPlayerController->SetStaminaAndTimer(GreatSwordEnhancedAttackStamina);
}

void AGreatSword::PlayJumpAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void AGreatSword::PlayDefenseStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(GreatSwordDefenseAnim, 1.f, FName("Start"));

	AttachToDefenseSocket(this, EKPlayer);
}

void AGreatSword::PlayDefenseTriggerAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(GreatSwordDefenseAnim, 1.f, FName("Loop"));
}

void AGreatSword::PlayDefenseReleaseAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(GreatSwordDefenseAnim, 1.f, FName("End"));

	AttachWeaponToHandSocket(this, EKPlayer);
}

void AGreatSword::PlayHitAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController)
	{
		return;
	}
	EKPlayer->PlayAnimMontage(GreatSwordHitAnim);
}

void AGreatSword::AttachToDefenseSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
{
	if (Weapon)
	{
		USkeletalMeshComponent* MeshComp = EKPlayer->GetMesh();
		if (MeshComp)
		{
			Weapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("greatsword_defense_socket"));
		}
	}
}