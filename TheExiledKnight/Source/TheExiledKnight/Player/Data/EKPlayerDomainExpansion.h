// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "EKPlayerDomainExpansion.generated.h"

USTRUCT(BlueprintType)
struct FEKPlayerDomainExpansion : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DomainExpansionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DomainExpansionName;
};