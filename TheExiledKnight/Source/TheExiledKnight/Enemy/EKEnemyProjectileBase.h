// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EKEnemyProjectileBase.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AEKEnemyProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEKEnemyProjectileBase();

	void SetHomingTarget(AActor* TargetActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


public:	
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh");
	class UStaticMeshComponent* ProjectileMesh; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrailParticle");
	class UParticleSystemComponent* TrailParticle; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileComponent");
	class UProjectileMovementComponent* ProjectileComponent; 
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* HitEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* HitSound; 
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting", meta = (AllowPrivateAccess = "true"))
	float InitialSpeed = 1000;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting", meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting", meta = (AllowPrivateAccess = "true"))
	float GravityScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting", meta = (AllowPrivateAccess = "true"))
	bool bIsRotation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting", meta = (AllowPrivateAccess = "true"))
	bool bIsHoming = true;
public:
	UBoxComponent* GetCollisionComponent();
};
