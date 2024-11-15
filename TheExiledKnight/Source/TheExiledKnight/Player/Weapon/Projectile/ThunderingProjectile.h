// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "ThunderingProjectile.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AThunderingProjectile : public AEKPlayerProjectile
{
	GENERATED_BODY()
	
public:	
	AThunderingProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};