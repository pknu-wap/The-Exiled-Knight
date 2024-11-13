// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EKEnemyAttackHitCheckNotfiyState.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UEKEnemyAttackHitCheckNotfiyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UEKEnemyAttackHitCheckNotfiyState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TSubclassOf<UDamageType> DamageTypeClass;

#pragma region NotifyState
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
#pragma endregion	


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Move)
	float MoveDistancePerSec;

private:
	
	float TotalDistance;
	float TotalTime;
	float AttackDamage;
	
	FVector StartLocation;
	
	AActor* Owner;

	TArray<AActor*>HitActors;

	FTimerHandle MoveTimerHandle;

	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	float  AttackRadius;

	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	float AttackHalfHeight;

	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	float  DamagePercentage = 1.0f;

	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	bool bAttackHitCheck; //debug line  or not

	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	FName StartSocketName;
	

};
