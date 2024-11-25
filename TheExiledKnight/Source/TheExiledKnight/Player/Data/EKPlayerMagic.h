// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "EKPlayerMagic.generated.h"

USTRUCT(BlueprintType)
struct FEKPlayerMagic : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagicID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MagicName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString MagicDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NeedMP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;
};