// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EKEnums.h"
#include "Widget_Equipment.generated.h"

class UWidgetSwitcher;
class UWidget_EquipSelectWindow;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_Equipment : public UUserWidget
{
	GENERATED_BODY()

public:
	void ShowEquipWindow();
	void ShowEquipSelect(EEquipCategory Category, int slotIdx);

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_EquipSelectWindow* EquipSelect;

public:
	FORCEINLINE int GetEquipSelectSlotIdx() { return SlotIdx_EquipSelect; }
private:
	int SlotIdx_EquipSelect = 0;
};
