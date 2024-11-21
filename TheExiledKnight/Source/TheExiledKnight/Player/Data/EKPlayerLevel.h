// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "EKPlayerLevel.generated.h"

USTRUCT(BlueprintType)
struct FEKPlayerLevel : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NeedSouls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DefaultDamage;
};