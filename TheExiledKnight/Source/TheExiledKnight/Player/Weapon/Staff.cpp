// Made by Somalia Pirate

#include "Staff.h"

AStaff::AStaff()
{
	PrimaryActorTick.bCanEverTick = true;

	Staff = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Staff"));
	RootComponent = Staff;

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaffMeshFinder(TEXT("/AssetShare/Animations/EssentialAnimation/MagicStaff/Demo/Mannequin/Weapon/SM_Staff"));
	if (StaffMeshFinder.Succeeded())
	{
		StaffMesh = StaffMeshFinder.Object;
	}
	Staff->SetStaticMesh(StaffMesh);

	WeaponCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	WeaponCapsuleComponent->SetupAttachment(RootComponent);
	WeaponCapsuleComponent->SetRelativeLocationAndRotation(FVector(0, -20, 0), FRotator(-90, 0, 90));
	WeaponCapsuleComponent->SetRelativeScale3D(FVector(1.f, 1.f, 2.f));
	WeaponCapsuleComponent->SetCapsuleRadius(11.f);
	WeaponCapsuleComponent->SetCapsuleHalfHeight(44.f);

	MaxAttackCombo = 4;
}

void AStaff::BeginPlay()
{
	Super::BeginPlay();

}

void AStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStaff::PlayWeaponEquipAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
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

void AStaff::PlayAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !StaffAttackAnim)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < StaffAttackStamina)
	{
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

	EKPlayerController->SetStaminaAndTimer(StaffAttackStamina);
}

void AStaff::PlayEnhancedAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void AStaff::PlayJumpAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void AStaff::PlayDefenseStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(StaffDefenseAnim, 1.f, FName("Start"));

	AttachToDefenseSocket(this, EKPlayer);
}

void AStaff::PlayDefenseTriggerAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(StaffDefenseAnim, 1.f, FName("Loop"));
}

void AStaff::PlayDefenseReleaseAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(StaffDefenseAnim, 1.f, FName("End"));

	AttachWeaponToHandSocket(this, EKPlayer);
}

void AStaff::PlayHitAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController)
	{
		return;
	}
	EKPlayer->PlayAnimMontage(StaffHitAnim);
}

void AStaff::AttachToDefenseSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
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

void AStaff::AttachWeaponToSpineSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
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

void AStaff::AttachWeaponToHandSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
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