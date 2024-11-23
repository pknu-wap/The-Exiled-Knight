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
#include "Item/EKItem_Base.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
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
	void PlayWeaponEquipAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController);

	virtual void PlayAttackStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController) PURE_VIRTUAL(AEKPlayerWeapon::PlayAttackStartAnimMontage, ;);

	virtual void PlaySkillStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController) PURE_VIRTUAL(AEKPlayerWeapon::PlaySkillStartAnimMontage, ;);

	virtual void AttachToDefenseSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer) PURE_VIRTUAL(AEKPlayerWeapon::AttachToDefenseSocket, ;);

public:
	virtual void AttachWeaponToSpineSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer);
	virtual void AttachWeaponToHandSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer);

public:
	virtual UCapsuleComponent* GetWeaponCapsuleComponent() { return nullptr; }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	uint8 MaxAttackCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	uint8 AttackCombo = 1;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float WeaponAdditionalDamage;

	void SetAttackComboNext();
	void ResetAttackCombo();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* WeaponEquipAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* WeaponUnEquipAnim;
};