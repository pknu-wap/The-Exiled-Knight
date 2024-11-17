// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyNotify/EKFireMagicSpellNotify.h"
#include "Enemy/EnemyWeapon/EKEnemyProjectileBase.h"
#include"Enemy/EK_EnemyStatusComponent.h"
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
		
		AActor* OwnerActor = MeshComp->GetOwner();
		if (OwnerActor)
		{
			SpawnedSpell->GetCollisionComponent()->IgnoreActorWhenMoving(OwnerActor, true);
		}
		AEK_EnemyBase* FireMagicEnemy = Cast<AEK_EnemyBase>(MeshComp->GetOwner());
		
		if (FireMagicEnemy) 
		{
			float TotalDamage = FireMagicEnemy->GetStatusComponent()->GetAttackDamage();
			TotalDamage *= DamagePercent;
			SpawnedSpell->SetDamage(TotalDamage);
			SpawnedSpell->SetHomingTarget(FireMagicEnemy->GetAttackTarget());
		}
	}

	
}
