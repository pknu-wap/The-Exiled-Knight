// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "EKPlayerWeapon.h"
#include "GreatSword.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AGreatSword : public AEKPlayerWeapon
{
	GENERATED_BODY()
	
public:	
	AGreatSword();

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
	TObjectPtr<class UStaticMeshComponent> GreatSword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class UStaticMesh> GreatSwordMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<UCapsuleComponent> WeaponCapsuleComponent;

	virtual TObjectPtr<UCapsuleComponent> GetWeaponCapsuleComponent() override;

public:
	virtual void AttackHit(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<UCapsuleComponent> WeaponCC) override;
};
