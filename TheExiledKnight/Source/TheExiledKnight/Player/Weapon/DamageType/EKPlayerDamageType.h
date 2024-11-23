// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "EKPlayerDamageType.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API UEKPlayerDamageType : public UDamageType
{
	GENERATED_BODY()
	
};

UCLASS()
class THEEXILEDKNIGHT_API UEKPlayerNormalDamageType : public UEKPlayerDamageType
{
	GENERATED_BODY()

};

UCLASS()
class THEEXILEDKNIGHT_API UEKPlayerStrongDamageType : public UEKPlayerDamageType
{
	GENERATED_BODY()

};