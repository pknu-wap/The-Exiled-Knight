// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "EKPlayerWeapon.h"
#include "Staff.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AStaff : public AEKPlayerWeapon
{
	GENERATED_BODY()
	
public:
	AStaff();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void PlayWeaponEquipAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) override;

	virtual void PlayAttackStartAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) override;

	virtual void PlayEnhancedAttackStartAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) override;

	virtual void PlayJumpAttackStartAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) override;

	virtual void PlayDefenseStartAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) override;
	virtual void PlayDefenseTriggerAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) override;
	virtual void PlayDefenseReleaseAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) override;

	virtual void PlayHitAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) override;

	virtual void AttachToDefenseSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<class AEKPlayer> EKPlayer) override;

public:
	virtual void AttachWeaponToSpineSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<class AEKPlayer> EKPlayer) override;
	virtual void AttachWeaponToHandSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<class AEKPlayer> EKPlayer) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class UStaticMeshComponent> Staff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class UStaticMesh> StaffMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class UCapsuleComponent> WeaponCapsuleComponent;

	virtual TObjectPtr<UCapsuleComponent> GetWeaponCapsuleComponent() override;

public:
	virtual void AttackHit(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<UCapsuleComponent> WeaponCC) override;
};