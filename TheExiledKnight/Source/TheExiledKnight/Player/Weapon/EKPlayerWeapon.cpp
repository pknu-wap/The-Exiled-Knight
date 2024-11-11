// Made by Somalia Pirate


#include "EKPlayerWeapon.h"
#include "../EKPlayer/EKPlayer.h"
#include "../EKPlayer/EKPlayerController.h"
#include "Subsystems/InventorySubsystem.h"
#include "Enemy/EK_EnemyStatusComponent.h"
#include"Enemy/EK_EnemyBase.h"
AEKPlayerWeapon::AEKPlayerWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEKPlayerWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AEKPlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEKPlayerWeapon::AttachWeaponToSpineSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer)
{
	if (Weapon)
	{
		USkeletalMeshComponent* MeshComp = EKPlayer->GetMesh();
		if (MeshComp)
		{
			Weapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("weapon_equip_socket"));
		}
	}
}

void AEKPlayerWeapon::AttachWeaponToHandSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer)
{
	if (Weapon)
	{
		USkeletalMeshComponent* MeshComp = EKPlayer->GetMesh();
		if (MeshComp)
		{
			Weapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("weapon_right_hand_socket"));
		}
	}
}

void AEKPlayerWeapon::SetAttackComboNext(uint8 MaxCombo)
{
	if (AttackCombo < MaxCombo)
	{
		AttackCombo++;
	}
	else
	{
		ResetAttackCombo();
	}
}

void AEKPlayerWeapon::ResetAttackCombo()
{
	AttackCombo = 1;
}