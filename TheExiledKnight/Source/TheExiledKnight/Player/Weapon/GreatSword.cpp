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
		if (!EKPlayerController->bIsEquipWeapon && EKPlayerController->GetEquipAnimGreatSword())
		{
			EKPlayer->PlayAnimMontage(EKPlayerController->GetEquipAnimGreatSword());
		}
		else if (EKPlayerController->bIsEquipWeapon && EKPlayerController->GetUnEquipAnimGreatSword())
		{
			EKPlayer->PlayAnimMontage(EKPlayerController->GetUnEquipAnimGreatSword());
		}
	}
}

void AGreatSword::PlayAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !EKPlayerController->GetGreatSwordAttackAnim())
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < GreatSwordAttackStamina)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetGreatSwordCombo() == 1)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetGreatSwordAttackAnim(), 1.0f, FName("Attack1"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetGreatSwordCombo() == 2 && EKPlayerController->bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetGreatSwordAttackAnim(), 1.0f, FName("Attack2"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetGreatSwordCombo() == 3 && EKPlayerController->bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetGreatSwordAttackAnim(), 1.0f, FName("Attack3"));
	}

	EKPlayerController->SetStaminaAndTimer(GreatSwordAttackStamina);
}

void AGreatSword::PlayEnhancedAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !EKPlayerController->GetGreatSwordAttackAnim())
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < GreatSwordEnhancedAttackStamina)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetGreatSwordEnhancedCombo() == 1)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetGreatSwordEnhancedAttackAnim(), 1.f, FName("Attack1"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetGreatSwordEnhancedCombo() == 2)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetGreatSwordEnhancedAttackAnim(), 1.f, FName("Attack2"));
	}

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

	EKPlayer->PlayAnimMontage(EKPlayerController->GetGreatSwordDefenseAnim(), 1.f, FName("Start"));

	AttachToDefenseSocket(this, EKPlayer);
}

void AGreatSword::PlayDefenseTriggerAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(EKPlayerController->GetGreatSwordDefenseAnim(), 1.f, FName("Loop"));
}

void AGreatSword::PlayDefenseReleaseAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(EKPlayerController->GetGreatSwordDefenseAnim(), 1.f, FName("End"));

	AttachWeaponToHandSocket(this, EKPlayer);
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

void AGreatSword::AttachWeaponToSpineSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
{
	Super::AttachWeaponToSpineSocket(Weapon, EKPlayer);
}

void AGreatSword::AttachWeaponToHandSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
{
	Super::AttachWeaponToHandSocket(Weapon, EKPlayer);
}

TObjectPtr<UCapsuleComponent> AGreatSword::GetWeaponCapsuleComponent()
{
	return WeaponCapsuleComponent;
}

void AGreatSword::AttackHit(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<UCapsuleComponent> WeaponCC)
{
	Super::AttackHit(EKPlayer, GetWeaponCapsuleComponent());
}