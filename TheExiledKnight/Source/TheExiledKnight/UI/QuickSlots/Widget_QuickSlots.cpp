// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/QuickSlots/Widget_QuickSlots.h"
#include "UI/QuickSlots/Widget_QuickSlot.h"

int UWidget_QuickSlots::GetActiveSlotIdx(EItemCategory InCategory)
{
	switch (InCategory)
	{
	case EItemCategory::None:
	{
		break;
	}
	case EItemCategory::Weapon:
	{
		return QuickSlot_Weapon->GetActiveSlotIdx();
		break;
	}
	case EItemCategory::Rune:
	{
		break;
	}
	case EItemCategory::FragmentOfGod:
	{
		return QuickSlot_Fragment->GetActiveSlotIdx();
		break;
	}
	case EItemCategory::UseableItem:
	{
		return QuickSlot_UseableItem->GetActiveSlotIdx();
		break;
	}
	case EItemCategory::Magic:
	{
		return QuickSlot_Magic->GetActiveSlotIdx();
		break;
	}
	default:
		break;
	}
    return 0;
}
