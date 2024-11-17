// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EKEnergyBeamNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UEKEnergyBeamNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UEKEnergyBeamNotifyState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TSubclassOf<UDamageType> DamageTypeClass;

#pragma region NotifyState

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

#pragma endregion

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Move)
	float MoveDistancePerSec; //Important 

private:

	float TotalDistance;
	float TotalTime;

	FVector StartLocation;

	AActor* Owner;

	FTimerHandle MoveTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	float  AttackRadius;

	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	float AttackHalfHeight;

	
	
	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	float AttackDamage;

	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	bool bAttackHitCheck;

	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	FName StartSocketName;
};
