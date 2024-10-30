// Fill out your copyright notice in the Description page of Project Settings.


#include "EKEnemyAnimNotifyState.h"
#include "EK_EnemyBase.h"
UEKEnemyAnimNotifyState::UEKEnemyAnimNotifyState()
{
	MoveDistancePerSec = 0;
	TotalTime = 0;
}

void UEKEnemyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	Owner = MeshComp->GetOwner();
	StartLocation = Owner->GetActorLocation();
	TotalDistance = TotalDuration * MoveDistancePerSec; // ��ü �̵� �Ÿ�
	// Begin ���� End ���� �ɸ��� �ð��� TotalDuration ���� �Ѿ�´�
	TotalTime = TotalDuration;

	if (Owner != nullptr)
	{
		Owner->GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
		Owner->GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle,
			FTimerDelegate::CreateLambda([this]()-> void
				{
					if (Owner != nullptr)
					{
						FVector TargetLocation = StartLocation + Owner->GetActorForwardVector() * TotalDistance;
						Owner->SetActorLocation(TargetLocation);
					}
				}
			)
			, TotalDuration
			, false
		);
	}
}

void UEKEnemyAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (Owner != nullptr)
	{
		AEK_EnemyBase* EnemyBase = Cast<AEK_EnemyBase>(Owner);
		if (EnemyBase)
		{
			// �� �����Ӹ��� ���� ������ ����
			EnemyBase->AttackHitCheck();
		}
		if (Owner->GetWorld()->GetTimerManager().IsTimerActive(MoveTimerHandle))
		{
			float ElapsedTime = Owner->GetWorld()->GetTimerManager().GetTimerElapsed(MoveTimerHandle);
			float Ratio = ElapsedTime / TotalTime;

			

			FVector TargetLocation = StartLocation + Owner->GetActorForwardVector() * Ratio * TotalDistance;
			Owner->SetActorLocation(TargetLocation);

		}
	}
}

void UEKEnemyAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (Owner != nullptr)
	{
		FVector FinalLocation = StartLocation + Owner->GetActorForwardVector() * TotalDistance;
		Owner->SetActorLocation(FinalLocation);
	}
}
