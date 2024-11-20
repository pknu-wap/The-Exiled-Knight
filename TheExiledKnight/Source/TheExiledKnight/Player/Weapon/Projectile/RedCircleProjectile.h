// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "RedCircleProjectile.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API ARedCircleProjectile : public AEKPlayerProjectile
{
	GENERATED_BODY()
	
public:	
	ARedCircleProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	TArray<FHitResult> HitResults;

protected:
	FTimerHandle DamageHandle;

	float DamageTime = 1.2f;

	bool bCanDamaged = true;

	void CanDamaged();

	void DamageTimer();
};