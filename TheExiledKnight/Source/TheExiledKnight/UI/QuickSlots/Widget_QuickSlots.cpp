// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/QuickSlots/Widget_QuickSlots.h"
#include "UI/QuickSlots/Widget_QuickSlot.h"

int UWidget_QuickSlots::GetActiveSlotIdx(EEquipCategory InCategory)
{
	switch (InCategory)
	{
	case EEquipCategory::None:
	{
		break;
	}
	case EEquipCategory::Weapon:
	{
		return QuickSlot_Weapon->GetActiveSlotIdx();
		break;
	}
	case EEquipCategory::Rune:
	{
		break;
	}
	case EEquipCategory::FragmentOfGod:
	{
		return QuickSlot_Fragment->GetActiveSlotIdx();
		break;
	}
	case EEquipCategory::UsableItem:
	{
		return QuickSlot_UsableItem->GetActiveSlotIdx();
		break;
	}
	case EEquipCategory::Magic:
	{
		return QuickSlot_Magic->GetActiveSlotIdx();
		break;
	}
	default:
		break;
	}
    return 0;
}
