// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EKEnemyAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UEKEnemyAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UEKEnemyAnimNotifyState();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	// 초당 이동거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Move)
	float MoveDistancePerSec;

private:
	// 전체 이동 거리
	float TotalDistance;
	// 전체 시간
	float TotalTime;
	// 시작위치
	FVector StartLocation;
	// 캐릭터
	AActor* Owner;
	// 이동 타이머
	FTimerHandle MoveTimerHandle;
};
