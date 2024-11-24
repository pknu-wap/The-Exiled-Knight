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

	class UBoxComponent* GetCollisionComponent();

	void SetHomingTarget(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TSubclassOf<UDamageType> DamageTypeClass;

	void SetDamage(float amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void HandleImpactEffects(const FVector& ImpactLocation);

public:	
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh");
	class UStaticMeshComponent* WeaponMesh; 

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
	float GravityScale=0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting", meta = (AllowPrivateAccess = "true"))
	bool bIsRotation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting", meta = (AllowPrivateAccess = "true"))
	bool bIsHoming = true;

	float TotalDamage = 30.0f;
public:
	
};
