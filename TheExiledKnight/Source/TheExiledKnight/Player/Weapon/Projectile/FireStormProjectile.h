// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "FireStormProjectile.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AFireStormProjectile : public AEKPlayerProjectile
{
	GENERATED_BODY()

public:
	AFireStormProjectile();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UStaticMeshComponent* StormMeshComponent;
};