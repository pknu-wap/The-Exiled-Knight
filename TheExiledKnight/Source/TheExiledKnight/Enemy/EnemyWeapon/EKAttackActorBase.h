// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EKAttackActorBase.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AEKAttackActorBase : public AActor
{
	GENERATED_BODY()
	
public:	

	AEKAttackActorBase();

	void SetDamage(float Amount);

	void SetInstigatorActor(AActor* Actor);
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	class  UBoxComponent* CollisionBox;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	float Damage=30.0f;
	
	TArray<AActor*> HitActors;

	AActor* InstigatorActor;

};
