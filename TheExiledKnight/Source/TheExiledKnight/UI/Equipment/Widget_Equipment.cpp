// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment/Widget_Equipment.h"
#include "UI/Equipment/Widget_EquipSelectWindow.h"
#include "Components/WidgetSwitcher.h"

void UWidget_Equipment::ShowEquipWindow()
{
	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void UWidget_Equipment::ShowEquipSelect(EEquipCategory Category, int slotIdx)
{
	// Save Slot Idx
	SlotIdx_EquipSelect = slotIdx;

	// Update Contents by Category
	EquipSelect->UpdateContents(Category);
	WidgetSwitcher->SetActiveWidgetIndex(1);
}
