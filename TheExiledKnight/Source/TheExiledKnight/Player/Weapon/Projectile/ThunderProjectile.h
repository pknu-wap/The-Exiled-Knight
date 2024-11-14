// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "ThunderProjectile.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AThunderProjectile : public AEKPlayerProjectile
{
	GENERATED_BODY()
	
public:	
	AThunderProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};