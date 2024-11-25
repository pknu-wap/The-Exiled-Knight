// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment/Widget_EquipSelect_ListElement.h"
#include "UI/Equipment/EquipSelect_ListData.h"
#include "UI/Equipment/Widget_EquipSelect_ContentSlot.h"

void UWidget_EquipSelect_ListElement::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UEquipSelect_ListData* data = Cast<UEquipSelect_ListData>(ListItemObject);
	if (!data) return;

	if (data->Category == EItemCategory::Magic)
	{
		if (data->Magics.IsValidIndex(0))
			Slot_01->UpdateSlot(data->Category, data->Magics[0]);

		if (data->Magics.IsValidIndex(1))
			Slot_02->UpdateSlot(data->Category, data->Magics[1]);

		if (data->Magics.IsValidIndex(2))
			Slot_03->UpdateSlot(data->Category, data->Magics[2]);

		if (data->Magics.IsValidIndex(3))
			Slot_04->UpdateSlot(data->Category, data->Magics[3]);

		if (data->Magics.IsValidIndex(4))
			Slot_05->UpdateSlot(data->Category, data->Magics[4]);
	}
	else
	{
		if (data->Items.IsValidIndex(0))
			Slot_01->UpdateSlot(data->Category, data->Items[0]);

		if (data->Items.IsValidIndex(1))
			Slot_02->UpdateSlot(data->Category, data->Items[1]);

		if (data->Items.IsValidIndex(2))
			Slot_03->UpdateSlot(data->Category, data->Items[2]);

		if (data->Items.IsValidIndex(3))
			Slot_04->UpdateSlot(data->Category, data->Items[3]);

		if (data->Items.IsValidIndex(4))
			Slot_05->UpdateSlot(data->Category, data->Items[4]);
	}
}
