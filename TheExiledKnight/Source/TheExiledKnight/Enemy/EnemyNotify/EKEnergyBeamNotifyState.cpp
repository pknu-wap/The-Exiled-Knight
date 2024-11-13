// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyNotify/EKEnergyBeamNotifyState.h"
#include"Player/EKPlayer/EKPlayer.h"
#include"Kismet/GameplayStatics.h"
#include"Player/EKPlayer//EKPlayerStatusComponent.h"
UEKEnergyBeamNotifyState::UEKEnergyBeamNotifyState()
{
	MoveDistancePerSec = 0;
	TotalTime = 0;
}

void UEKEnergyBeamNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	Owner = MeshComp->GetOwner();
	
	StartLocation = Owner->GetActorLocation();
	TotalDistance = TotalDuration * MoveDistancePerSec;
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

void UEKEnergyBeamNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

#pragma region AttackHitCheck
	if (Owner != nullptr)
	{
		FVector   SocketLocation = MeshComp->GetSocketLocation(StartSocketName);
		FVector   SocketForward = MeshComp->GetSocketRotation(StartSocketName).Vector();

		FVector AttackRangeStart = SocketLocation;
		FVector AttackRangeEnd = SocketLocation + SocketForward * AttackHalfHeight * 2;
		if (bAttackHitCheck) {
			DrawDebugCapsule(MeshComp->GetWorld(), (AttackRangeStart + AttackRangeEnd) * 0.5f, AttackHalfHeight, AttackRadius,
				FRotationMatrix::MakeFromZ(AttackRangeEnd - AttackRangeStart).ToQuat(), FColor::Red, false, 0.2f);
		}

		FCollisionQueryParams Params(NAME_None, false, Owner);
		TArray<FHitResult> HitResults;

		bool bHit = MeshComp->GetWorld()->SweepMultiByChannel(
			HitResults,
			AttackRangeStart,
			AttackRangeEnd,
			FQuat::Identity,
			ECC_Pawn,
			FCollisionShape::MakeCapsule(AttackRadius, AttackHalfHeight)
		);

		if (bHit)
		{
			float Damage = AttackDamage;

			for (const FHitResult& Hit : HitResults)
			{
				AActor* HitActor = Hit.GetActor();
				if (HitActor)
				{
					AEKPlayer* DetectedPlayer = Cast<AEKPlayer>(HitActor);
					if (DetectedPlayer)
					{
						UGameplayStatics::ApplyDamage(HitActor, Damage, Hit.GetActor()->GetInstigatorController(), HitActor, DamageTypeClass);
					}
				}
			}
		}
#pragma endregion

		if (Owner->GetWorld()->GetTimerManager().IsTimerActive(MoveTimerHandle))
		{
			float ElapsedTime = Owner->GetWorld()->GetTimerManager().GetTimerElapsed(MoveTimerHandle);
			float Ratio = ElapsedTime / TotalTime;

			FVector TargetLocation = StartLocation + Owner->GetActorForwardVector() * Ratio * TotalDistance;
			Owner->SetActorLocation(TargetLocation);

		}
	}
	
}

void UEKEnergyBeamNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (Owner != nullptr)
	{
		FVector FinalLocation = StartLocation + Owner->GetActorForwardVector() * TotalDistance;
		Owner->SetActorLocation(FinalLocation);
	}
}

