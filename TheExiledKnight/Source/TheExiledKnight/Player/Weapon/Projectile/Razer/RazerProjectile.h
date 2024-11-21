// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "RazerProjectile.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API ARazerProjectile : public AEKPlayerProjectile
{
	GENERATED_BODY()
	
public:	
	ARazerProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};