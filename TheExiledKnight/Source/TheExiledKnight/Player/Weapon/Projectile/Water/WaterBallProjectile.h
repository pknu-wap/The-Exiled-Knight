// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "WaterBallProjectile.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AWaterBallProjectile : public AEKPlayerProjectile
{
	GENERATED_BODY()
	
public:	
	AWaterBallProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	TArray<AEK_EnemyBase*> IgnoreEnemy;

};