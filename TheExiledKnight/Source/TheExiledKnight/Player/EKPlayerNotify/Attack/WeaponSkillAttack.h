// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Player/EKPlayer/EKPlayer.h"
#include "Player/EKPlayer/EKPlayerController.h"
#include "Player/EKPlayerGameplayTags.h"
#include "Player/Weapon/EKPlayerWeapon.h"
#include "Player/Weapon/DamageType/EKPlayerDamageType.h"
#include "Enemy/EK_EnemyBase.h"
#include "WeaponSkillAttack.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API UWeaponSkillAttack : public UAnimNotifyState
{
	GENERATED_BODY()
	
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	AEKPlayer* EKPlayer;

	AEKPlayerController* EKPlayerController;

protected:
	TArray<AEK_EnemyBase*> IgnoreEnemy;

protected:
	// Edit Editer Notify Damege Coefficient Value
	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageValue = 1.0;
};