// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "EKPlayerStatus.generated.h"

USTRUCT(BlueprintType)
struct FEKPlayerStatus : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StatusLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Vitality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Mental;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Endurance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Ability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Intelligence;
};