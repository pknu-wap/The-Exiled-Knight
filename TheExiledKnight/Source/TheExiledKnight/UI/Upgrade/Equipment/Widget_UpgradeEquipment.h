// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/InventorySlotStruct.h"
#include "Widget_UpgradeEquipment.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UWidget_UpgradeEquipment : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDescription(const FInventorySlot& SlotData);
};
