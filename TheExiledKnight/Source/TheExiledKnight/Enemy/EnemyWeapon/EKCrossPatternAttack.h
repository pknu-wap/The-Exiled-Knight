// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyWeapon/EKAttackActorBase.h"
#include "EKCrossPatternAttack.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API AEKCrossPatternAttack : public AEKAttackActorBase
{
	GENERATED_BODY()

public:
	AEKCrossPatternAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	UBoxComponent* SecondCollisionBox;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
