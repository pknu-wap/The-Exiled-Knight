// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "FireBallProjectile.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AFireBallProjectile : public AEKPlayerProjectile
{
	GENERATED_BODY()
	
public:	
	AFireBallProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};