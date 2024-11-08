// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyNotify/EKFireMagicSpellNotify.h"
#include "Enemy/EKEnemyProjectileBase.h"
#include"Enemy/EK_EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include"Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

void UEKFireMagicSpellNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MagicSpell || !MeshComp)return;
	if (!MeshComp->DoesSocketExist(SocketName))return;
	
	FVector SpawnLocation = MeshComp->GetSocketLocation(SocketName);

	FRotator SpawnRotation = MeshComp->GetSocketRotation(SocketName);

	AEKEnemyProjectileBase* SpawnedSpell = MeshComp->GetWorld()->SpawnActor<AEKEnemyProjectileBase>(MagicSpell, SpawnLocation, SpawnRotation);

	
	if (SpawnedSpell)
	{
		// 발사체가 발사 주체와 충돌을 무시하도록 설정
		AActor* OwnerActor = MeshComp->GetOwner();
		if (OwnerActor)
		{
			SpawnedSpell->GetCollisionComponent()->IgnoreActorWhenMoving(OwnerActor, true);
		}
		AEK_EnemyBase* FireMagicEnemy = Cast<AEK_EnemyBase>(MeshComp->GetOwner());

		if (FireMagicEnemy) 
		{
			SpawnedSpell->SetHomingTarget(FireMagicEnemy->GetAttackTarget());
		}
	}

	
}
