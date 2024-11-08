// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Enemy/EK_EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "../EKPlayer/EKPlayer.h"
#include "../EKPlayer/EKPlayerController.h"
#include "../EKPlayer/EKPlayerStatusComponent.h"
#include "../EKPlayerGameplayTags.h"
#include "EKPlayerWeapon.generated.h"

UCLASS(Abstract)
class THEEXILEDKNIGHT_API AEKPlayerWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AEKPlayerWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void PlayWeaponEquipAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) PURE_VIRTUAL(AEKPlayerWeapon::PlayWeaponEquipAnimMontage, ;);

	virtual void PlayAttackStartAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) PURE_VIRTUAL(AEKPlayerWeapon::PlayAttackStartAnimMontage, ;);

	virtual void PlayEnhancedAttackStartAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) PURE_VIRTUAL(AEKPlayerWeapon::PlayEnhancedAttackStartAnimMontage, ;);

	virtual void PlayJumpAttackStartAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) PURE_VIRTUAL(AEKPlayerWeapon::PlayJumpAttackStartAnimMontage, ;);

	virtual void AttachToDefenseSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<class AEKPlayer> EKPlayer) PURE_VIRTUAL(AEKPlayerWeapon::AttachToDefenseSocket, ;);

public:
	virtual void AttachWeaponToSpineSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<class AEKPlayer> EKPlayer);
	virtual void AttachWeaponToHandSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<class AEKPlayer> EKPlayer);

public:
	virtual TObjectPtr<UCapsuleComponent> GetWeaponCapsuleComponent() { return nullptr; }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	uint8 MaxAttackCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	uint8 AttackCombo = 1;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	uint32 WeaponAdditionalDamage;

	void SetAttackComboNext(uint8 MaxCombo);
	void ResetAttackCombo();
};