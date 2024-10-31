// Made by Somalia Pirate


#include "EKPlayerWeapon.h"
#include "../EKPlayer/EKPlayer.h"
#include "../EKPlayer/EKPlayerController.h"
#include "Subsystems/InventorySubsystem.h"
#include "../../Enemy/EK_EnemyStatusComponent.h"
#include "../../Enemy/EK_EnemyBase.h"

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

void AEKPlayerWeapon::PlayHitAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController)
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

void AEKPlayerWeapon::AttackHit(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<UCapsuleComponent> WeaponCC)
{
	FVector CapsuleLocation = WeaponCC->GetComponentLocation();
	FRotator CapsuleRotation = WeaponCC->GetComponentRotation();
	float CapsuleHalfHeight = WeaponCC->GetScaledCapsuleHalfHeight();
	float CapsuleRadius = WeaponCC->GetScaledCapsuleRadius();

	FCollisionQueryParams Params(NAME_None, false, this);
	TArray<FHitResult> HitResults;

	//DrawDebugCapsule(GetWorld(), CapsuleLocation, CapsuleHalfHeight, CapsuleRadius, CapsuleRotation.Quaternion(), FColor::Red, false, 0.3f);

	EKPlayer->bIsHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		CapsuleLocation,
		CapsuleLocation,
		CapsuleRotation.Quaternion(),
		ECC_Pawn,
		FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight),
		Params
	);

	if (!EKPlayer->bIsHit)
	{
		return;
	}

	for (auto& Hit : HitResults)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			TObjectPtr<AEK_EnemyBase> HitEnemy = Cast<AEK_EnemyBase>(HitActor);
			if (HitEnemy)
			{
				HitEnemy->GetStatusComponent()->TakeDamage(1);
				EKPlayer->bIsHitOnce = true;
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Attack!!!"));
			}
		}
	}
}

TObjectPtr<UCapsuleComponent> AEKPlayerWeapon::GetWeaponCapsuleComponent()
{
	return nullptr;
}