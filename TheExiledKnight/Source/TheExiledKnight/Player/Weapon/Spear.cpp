// Made by Somalia Pirate


#include "Spear.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"

ASpear::ASpear()
{
	PrimaryActorTick.bCanEverTick = true;

	Spear = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Spear"));
	RootComponent = Spear;

	Spear->SetSkeletalMesh(SpearMesh);

	WeaponCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	WeaponCapsuleComponent->SetupAttachment(RootComponent);
	WeaponCapsuleComponent->SetRelativeLocationAndRotation(FVector(30, 0, 0), FRotator(-90, 0, 0));
	WeaponCapsuleComponent->SetRelativeScale3D(FVector(1.f, 1.f, 3.f));
	WeaponCapsuleComponent->SetCapsuleRadius(11.f);
	WeaponCapsuleComponent->SetCapsuleHalfHeight(44.f);

	MaxAttackCombo = 5;

	WeaponAdditionalDamage = 10;
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
		if (!EKPlayerController->bIsEquipWeapon && SpearEquipAnim)
		{
			EKPlayer->PlayAnimMontage(SpearEquipAnim);
		}
		else if (EKPlayerController->bIsEquipWeapon && SpearUnEquipAnim)
		{
			EKPlayer->PlayAnimMontage(SpearUnEquipAnim);
		}
	}
}

#pragma region Attack

void ASpear::PlayAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !SpearAttackAnim)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < SpearAttackStamina)
	{
		return;
	}

	if (AttackCombo == 1)
	{
		EKPlayer->StopAnimMontage(SpearAttackAnim);
		EKPlayer->PlayAnimMontage(SpearAttackAnim, 1.0f, FName("Attack1"));
		EKPlayerController->SetAttackEndTimer(1.0f);
	}
	else if (AttackCombo == 2)
	{
		EKPlayer->StopAnimMontage(SpearAttackAnim);
		EKPlayer->PlayAnimMontage(SpearAttackAnim, 1.0f, FName("Attack2"));
		EKPlayerController->SetAttackEndTimer(1.0f);
	}
	else if (AttackCombo == 3)
	{
		EKPlayer->StopAnimMontage(SpearAttackAnim);
		EKPlayer->PlayAnimMontage(SpearAttackAnim, 1.0f, FName("Attack3"));
		EKPlayerController->SetAttackEndTimer(0.83f);
	}
	else if (AttackCombo == 4)
	{
		EKPlayer->StopAnimMontage(SpearAttackAnim);
		EKPlayer->PlayAnimMontage(SpearAttackAnim, 1.0f, FName("Attack4"));
		EKPlayerController->SetAttackEndTimer(1.25f);
	}
	else if (AttackCombo == 5)
	{
		EKPlayer->StopAnimMontage(SpearAttackAnim);
		EKPlayer->PlayAnimMontage(SpearAttackAnim, 1.0f, FName("Attack5"));
		EKPlayerController->SetAttackEndTimer(1.33f);
	}

	EKPlayerController->ConsumtionStaminaAndTimer(SpearAttackStamina);
}

void ASpear::PlayEnhancedAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void ASpear::PlayJumpAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

#pragma endregion

#pragma region Defense and Hit

void ASpear::PlayDefenseStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(SpearDefenseAnim, 1.f, FName("Start"));

	AttachToDefenseSocket(this, EKPlayer);
}

void ASpear::PlayDefenseTriggerAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(SpearDefenseAnim, 1.f, FName("Loop"));
}

void ASpear::PlayDefenseReleaseAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(SpearDefenseAnim, 1.f, FName("End"));

	AttachWeaponToHandSocket(this, EKPlayer);
}

void ASpear::PlayDefenseHitAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	EKPlayer->StopAnimMontage(SpearDefenseAnim);
	EKPlayer->PlayAnimMontage(SpearDefenseAnim, 1.f, FName("Hit"));
}

void ASpear::PlayDefenseBrokenAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	EKPlayer->StopAnimMontage(SpearDefenseAnim);
	EKPlayer->PlayAnimMontage(SpearDefenseAnim, 1.f, FName("Broken"));
}

void ASpear::PlayHitAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	EKPlayer->PlayAnimMontage(SpearHitAnim);
}

#pragma endregion

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