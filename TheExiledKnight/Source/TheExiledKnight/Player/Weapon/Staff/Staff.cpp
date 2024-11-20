// Made by Somalia Pirate

#include "Staff.h"

AStaff::AStaff()
{
	PrimaryActorTick.bCanEverTick = true;

	Staff = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Staff"));
	RootComponent = Staff;

	Staff->SetStaticMesh(StaffMesh);

	WeaponCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	WeaponCapsuleComponent->SetRelativeLocationAndRotation(FVector(0, -20, 0), FRotator(-90, 0, 90));
	WeaponCapsuleComponent->SetRelativeScale3D(FVector(1.f, 1.f, 2.f));
	WeaponCapsuleComponent->SetCapsuleRadius(11.f);
	WeaponCapsuleComponent->SetCapsuleHalfHeight(44.f);
	WeaponCapsuleComponent->SetupAttachment(RootComponent);

	MaxAttackCombo = 4;

	WeaponAdditionalDamage = 5;
}

void AStaff::BeginPlay()
{
	Super::BeginPlay();

}

void AStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStaff::PlayWeaponEquipAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController)
{
	if (EKPlayer && EKPlayerController)
	{
		if (!EKPlayerController->bIsEquipWeapon && StaffEquipAnim)
		{
			EKPlayer->PlayAnimMontage(StaffEquipAnim);
		}
		else if (EKPlayerController->bIsEquipWeapon && StaffUnEquipAnim)
		{
			EKPlayer->PlayAnimMontage(StaffUnEquipAnim);
		}
	}
}

#pragma region Attack

void AStaff::PlayAttackStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !StaffAttackAnim || !StaffAttackMagicAnim)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetMp() < StaffAttackMp)
	{
		if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < StaffAttackStamina)
		{
			EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
			return;
		}

		if (AttackCombo == 1)
		{
			EKPlayer->StopAnimMontage(StaffAttackAnim);
			EKPlayer->PlayAnimMontage(StaffAttackAnim, 1.0f, FName("Attack1"));
			EKPlayerController->SetAttackEndTimer(2.33f);
		}
		else if (AttackCombo == 2)
		{
			EKPlayer->StopAnimMontage(StaffAttackAnim);
			EKPlayer->PlayAnimMontage(StaffAttackAnim, 1.0f, FName("Attack2"));
			EKPlayerController->SetAttackEndTimer(2.67f);
		}
		else if (AttackCombo == 3)
		{
			EKPlayer->StopAnimMontage(StaffAttackAnim);
			EKPlayer->PlayAnimMontage(StaffAttackAnim, 1.0f, FName("Attack3"));
			EKPlayerController->SetAttackEndTimer(3.33f);
		}
		else if (AttackCombo == 4)
		{
			EKPlayer->StopAnimMontage(StaffAttackAnim);
			EKPlayer->PlayAnimMontage(StaffAttackAnim, 1.0f, FName("Attack4"));
			EKPlayerController->SetAttackEndTimer(2.67f);
		}

		EKPlayerController->ConsumtionStaminaAndTimer(StaffAttackStamina);
	}
	else
	{
		EKPlayer->StopAnimMontage(StaffAttackMagicAnim);
		EKPlayer->PlayAnimMontage(StaffAttackMagicAnim);
		EKPlayerController->RemoveAttackTagTimer(StaffAttackMagicAnim->GetPlayLength());
		EKPlayer->GetPlayerStatusComponent()->SetMp(-StaffAttackMp);
	}
}

#pragma endregion

#pragma region Attach to Socket

void AStaff::AttachToDefenseSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer)
{
	if (Weapon)
	{
		USkeletalMeshComponent* MeshComp = EKPlayer->GetMesh();
		if (MeshComp)
		{
			Weapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("staff_defense_socket"));
		}
	}
}

void AStaff::AttachWeaponToSpineSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer)
{
	if (Weapon)
	{
		USkeletalMeshComponent* MeshComp = EKPlayer->GetMesh();
		if (MeshComp)
		{
			Weapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("staff_equip_socket"));
		}
	}
}

void AStaff::AttachWeaponToHandSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer)
{
	if (Weapon)
	{
		USkeletalMeshComponent* MeshComp = EKPlayer->GetMesh();
		if (MeshComp)
		{
			Weapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("staff_right_hand_socket"));
		}
	}
}

#pragma endregion