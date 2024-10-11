// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EKPlayerWeapon.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AEKPlayerWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AEKPlayerWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
