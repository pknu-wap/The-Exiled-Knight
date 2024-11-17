// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structs/ItemStruct.h"
#include "Structs/InventorySlotStruct.h"
#include "EKEnums.h"
#include "EquipSelect_ListData.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UEquipSelect_ListData : public UObject
{
	GENERATED_BODY()
	
public:
	EItemCategory Category;

	TArray<FInventorySlot> Items;
};
