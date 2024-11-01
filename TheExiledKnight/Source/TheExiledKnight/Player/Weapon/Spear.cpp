// Made by Somalia Pirate


#include "Spear.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"

ASpear::ASpear()
{
	PrimaryActorTick.bCanEverTick = true;

	Spear = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Spear"));
	RootComponent = Spear;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SpearMeshFinder(TEXT("/AssetShare/Animations/Frank_Spear/Mesh/Frank_UE_Spear_Weapon_Skin"));
	if (SpearMeshFinder.Succeeded())
	{
		SpearMesh = SpearMeshFinder.Object;
	}
	Spear->SetSkeletalMesh(SpearMesh);

	WeaponCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	WeaponCapsuleComponent->SetupAttachment(RootComponent);
	WeaponCapsuleComponent->SetRelativeLocationAndRotation(FVector(60, 0, 0), FRotator(-90, 0, 0));
	WeaponCapsuleComponent->SetRelativeScale3D(FVector(1.f, 1.f, 3.f));
}

void ASpear::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpear::PlayWeaponEquipAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (EKPlayer && EKPlayerController)
	{
		if (!EKPlayerController->bIsEquipWeapon && EKPlayerController->GetEquipAnimSpear())
		{
			EKPlayer->PlayAnimMontage(EKPlayerController->GetEquipAnimSpear());
		}
		else if (EKPlayerController->bIsEquipWeapon && EKPlayerController->GetUnEquipAnimSpear())
		{
			EKPlayer->PlayAnimMontage(EKPlayerController->GetUnEquipAnimSpear());
		}
	}
}

void ASpear::PlayAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !EKPlayerController->GetSpearAttackAnim())
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < SpearAttackStamina)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 1)
	{
		EKPlayer->StopAnimMontage(EKPlayerController->GetSpearAttackAnim());
		EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearAttackAnim(), 1.0f, FName("Attack1"));
		EKPlayerController->SetAttackEndTimer(1.0f);
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 2)
	{
		EKPlayer->StopAnimMontage(EKPlayerController->GetSpearAttackAnim());
		EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearAttackAnim(), 1.0f, FName("Attack2"));
		EKPlayerController->SetAttackEndTimer(1.0f);
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 3)
	{
		EKPlayer->StopAnimMontage(EKPlayerController->GetSpearAttackAnim());
		EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearAttackAnim(), 1.0f, FName("Attack3"));
		EKPlayerController->SetAttackEndTimer(0.83f);
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 4)
	{
		EKPlayer->StopAnimMontage(EKPlayerController->GetSpearAttackAnim());
		EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearAttackAnim(), 1.0f, FName("Attack4"));
		EKPlayerController->SetAttackEndTimer(1.25f);
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 5)
	{
		EKPlayer->StopAnimMontage(EKPlayerController->GetSpearAttackAnim());
		EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearAttackAnim(), 1.0f, FName("Attack5"));
		EKPlayerController->SetAttackEndTimer(1.33f);
	}

	EKPlayerController->SetStaminaAndTimer(SpearAttackStamina);
}

void ASpear::PlayEnhancedAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void ASpear::PlayJumpAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void ASpear::PlayDefenseStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearDefenseAnim(), 1.f, FName("Start"));

	AttachToDefenseSocket(this, EKPlayer);
}

void ASpear::PlayDefenseTriggerAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearDefenseAnim(), 1.f, FName("Loop"));
}

void ASpear::PlayDefenseReleaseAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearDefenseAnim(), 1.f, FName("End"));

	AttachWeaponToHandSocket(this, EKPlayer);
}

void ASpear::PlayHitAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController)
	{
		return;
	}
	EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearHitAnim());
}

void ASpear::AttachToDefenseSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
{
	if (Weapon)
	{
		USkeletalMeshComponent* MeshComp = EKPlayer->GetMesh();
		if (MeshComp)
		{
			Weapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("spear_defense_socket"));
		}
	}
}

void ASpear::AttachWeaponToSpineSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
{
	Super::AttachWeaponToSpineSocket(Weapon, EKPlayer);
}

void ASpear::AttachWeaponToHandSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
{
	Super::AttachWeaponToHandSocket(Weapon, EKPlayer);
}

TObjectPtr<UCapsuleComponent> ASpear::GetWeaponCapsuleComponent()
{
	return WeaponCapsuleComponent;
}

void ASpear::AttackHit(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<UCapsuleComponent> WeaponCC)
{
	Super::AttackHit(EKPlayer, GetWeaponCapsuleComponent());
}