// Fill out your copyright notice in the Description page of Project Settings.


#include "EK_EnemyBase.h"
#include "EK_EnemyStatusComponent.h"
// Sets default values
AEK_EnemyBase::AEK_EnemyBase()
{
	EnemyStat = CreateDefaultSubobject<UEK_EnemyStatusComponent>(TEXT("EnemyStat"));
}

void AEK_EnemyBase::AttackHitCheck()
{
	USkeletalMeshComponent* SkeletalMeshComp = FindComponentByClass<USkeletalMeshComponent>();
	if (!SkeletalMeshComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("SkeletalMeshComponent not found on %s"), *GetName());
		return;
	}
	FVector  SocketLocation = SkeletalMeshComp->GetSocketLocation("Attack_Socket");
	FVector   SocketForward = SkeletalMeshComp->GetSocketRotation("Attack_Socket").Vector();
	
	FVector AttackRangeStart = SocketLocation;
	FVector AttackRangeEnd = SocketLocation + SocketForward * AttackHalfHeight * 2;
	DrawDebugCapsule(GetWorld(), (AttackRangeStart + AttackRangeEnd) * 0.5f, AttackHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(AttackRangeEnd - AttackRangeStart).ToQuat(), FColor::Red, false, 0.2f);
	FCollisionQueryParams Params(NAME_None, false, this);
	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams(NAME_None, false, this);
	
	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		AttackRangeStart,
		AttackRangeEnd,
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeCapsule(AttackRadius, AttackHalfHeight)
	);
	if (bHit)
	{
		for (auto& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitActor->GetName());
			}
		}
	}
}






