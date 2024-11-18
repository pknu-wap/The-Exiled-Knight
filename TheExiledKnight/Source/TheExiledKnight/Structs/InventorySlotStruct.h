// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EKEnums.h"
#include "ItemStruct.h"
#include "InventorySlotStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct THEEXILEDKNIGHT_API FInventorySlot
{
	GENERATED_BODY()

	FInventorySlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemStruct Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Quantity = 0;
};
