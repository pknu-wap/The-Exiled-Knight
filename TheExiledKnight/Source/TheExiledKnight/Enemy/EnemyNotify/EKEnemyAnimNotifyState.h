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
	// �ʴ� �̵��Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Move)
	float MoveDistancePerSec;

private:
	// ��ü �̵� �Ÿ�
	float TotalDistance;
	// ��ü �ð�
	float TotalTime;
	// ������ġ
	FVector StartLocation;
	// ĳ����
	AActor* Owner;
	// �̵� Ÿ�̸�
	FTimerHandle MoveTimerHandle;
};
