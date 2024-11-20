// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "HealCircleProjectile.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AHealCircleProjectile : public AEKPlayerProjectile
{
	GENERATED_BODY()
	
public:	
	AHealCircleProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	FTimerHandle HealHandle;

	float HealTime = 2.f;

	bool bCanHeal = true;

	void CanHeal();

	void HealTimer();
};