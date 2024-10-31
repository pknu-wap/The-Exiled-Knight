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
	WeaponCapsuleComponent->SetRelativeLocationAndRotation(FVector(60, 0, 0), FRotator(-90, 0, 0));
	WeaponCapsuleComponent->SetRelativeScale3D(FVector(1.f, 1.f, 3.f));
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
		if (!EKPlayerController->bIsEquipWeapon && EKPlayerController->GetEquipAnimStaff())
		{
			EKPlayer->PlayAnimMontage(EKPlayerController->GetEquipAnimStaff());
		}
		else if (EKPlayerController->bIsEquipWeapon && EKPlayerController->GetUnEquipAnimStaff())
		{
			EKPlayer->PlayAnimMontage(EKPlayerController->GetUnEquipAnimStaff());
		}
	}
}

void AStaff::PlayAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !EKPlayerController->GetStaffAttackAnim())
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < StaffAttackStamina)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStaffCombo() == 1)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetStaffAttackAnim(), 1.0f, FName("Attack1"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetStaffCombo() == 2 && EKPlayerController->bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetStaffAttackAnim(), 1.0f, FName("Attack2"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetStaffCombo() == 3 && EKPlayerController->bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetStaffAttackAnim(), 1.0f, FName("Attack3"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetStaffCombo() == 4 && EKPlayerController->bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetStaffAttackAnim(), 1.0f, FName("Attack4"));
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

	EKPlayer->PlayAnimMontage(EKPlayerController->GetStaffDefenseAnim(), 1.f, FName("Start"));

	AttachToDefenseSocket(this, EKPlayer);
}

void AStaff::PlayDefenseTriggerAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(EKPlayerController->GetStaffDefenseAnim(), 1.f, FName("Loop"));
}

void AStaff::PlayDefenseReleaseAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController || !EKPlayerController->bIsEquipWeapon)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(EKPlayerController->GetStaffDefenseAnim(), 1.f, FName("End"));

	AttachWeaponToHandSocket(this, EKPlayer);
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

TObjectPtr<UCapsuleComponent> AStaff::GetWeaponCapsuleComponent()
{
	return WeaponCapsuleComponent;
}

void AStaff::AttackHit(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<UCapsuleComponent> WeaponCC)
{
	Super::AttackHit(EKPlayer, GetWeaponCapsuleComponent());
}