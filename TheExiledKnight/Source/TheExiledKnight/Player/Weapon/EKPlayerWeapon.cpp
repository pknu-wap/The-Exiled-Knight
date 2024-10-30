// Made by Somalia Pirate


#include "EKPlayerWeapon.h"
#include "../EKPlayer/EKPlayer.h"
#include "../EKPlayer/EKPlayerController.h"

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

void AEKPlayerWeapon::PlayWeaponEquipAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void AEKPlayerWeapon::PlayAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void AEKPlayerWeapon::PlayEnhancedAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void AEKPlayerWeapon::PlayJumpAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void AEKPlayerWeapon::PlayDefenseStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void AEKPlayerWeapon::PlayDefenseTriggerAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void AEKPlayerWeapon::PlayDefenseReleaseAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{

}

void AEKPlayerWeapon::AttachToDefenseSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<class AEKPlayer> EKPlayer)
{

}

void AEKPlayerWeapon::AttachWeaponToSpineSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
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

void AEKPlayerWeapon::AttachWeaponToHandSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
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