// Fill out your copyright notice in the Description page of Project Settings.


#include "EKEnemyAttackHitCheckNotfiyState.h"
#include "Enemy/EK_EnemyBase.h"
#include "Enemy/EK_EnemyStatusComponent.h"
#include"Player/EKPlayer/EKPlayer.h"
#include"Kismet/GameplayStatics.h"
#include"Components/CapsuleComponent.h"
#include"Player/EKPlayer//EKPlayerStatusComponent.h"

UEKEnemyAttackHitCheckNotfiyState::UEKEnemyAttackHitCheckNotfiyState()
{
	MoveDistancePerSec = 0;
	TotalTime = 0;
}

void UEKEnemyAttackHitCheckNotfiyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	
	HitActors.Empty(); 
	Owner =MeshComp->GetOwner();
	AEK_EnemyBase* OwnerEnemy = Cast<AEK_EnemyBase>(Owner); 
	if (OwnerEnemy && OwnerEnemy->GetStatusComponent())  // OwnerEnemy�� StatusComponent ��ȿ�� �˻�
	{
		AttackDamage = OwnerEnemy->GetStatusComponent()->GetAttackDamage();
	}
	
	StartLocation = Owner->GetActorLocation();
	TotalDistance = TotalDuration * MoveDistancePerSec; //Total distance
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
void UEKEnemyAttackHitCheckNotfiyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (Owner != nullptr)
	{
#pragma region AttackHitCheck

		
		FVector   SocketLocation = MeshComp->GetSocketLocation(StartSocketName);
		FVector   SocketForward = MeshComp->GetSocketRotation(StartSocketName).Vector();

		FVector AttackRangeStart = SocketLocation;
		FVector AttackRangeEnd = SocketLocation + SocketForward * AttackHalfHeight * 2;
		if (bAttackHitCheck) {
			DrawDebugCapsule(MeshComp->GetWorld(), (AttackRangeStart + AttackRangeEnd) * 0.5f, AttackHalfHeight, AttackRadius,
				FRotationMatrix::MakeFromZ(AttackRangeEnd - AttackRangeStart).ToQuat(), FColor::Green, false, 0.5f);
		}
		FCollisionQueryParams Params(NAME_None, false, Owner);

		TArray<FHitResult> HitResults;
		
		 //what 's  matter ? : GetWorld (): not object 
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
			float Damage = AttackDamage * DamagePercentage;

			for (const FHitResult& Hit : HitResults)
			{
				AActor* HitActor = Hit.GetActor();
				if (HitActor&&!HitActors.Contains(HitActor))
				{
					AEKPlayer* DetectedPlayer = Cast<AEKPlayer>(HitActor);
					if (DetectedPlayer)
					{
						UGameplayStatics::ApplyDamage(HitActor, Damage, Hit.GetActor()->GetInstigatorController(), Owner, DamageTypeClass);   
						HitActors.Add(HitActor);
					
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
void UEKEnemyAttackHitCheckNotfiyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (Owner != nullptr)
	{
		FVector FinalLocation = StartLocation + Owner->GetActorForwardVector() * TotalDistance;
		Owner->SetActorLocation(FinalLocation);
	}
}


