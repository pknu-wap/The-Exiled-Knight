// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "ThunderBallProjectile.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AThunderBallProjectile : public AEKPlayerProjectile
{
	GENERATED_BODY()
	
public:	
	AThunderBallProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};