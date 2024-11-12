// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/QuickSlots/Widget_QuickSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SlotComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UWidget_QuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!playerController) return;
	USlotComponent* slotComp = playerController->GetComponentByClass<USlotComponent>();
	if (!slotComp) return;

	slotComp->Delegate_SlotUpdated.RemoveAll(this);
	slotComp->Delegate_SlotUpdated.AddUObject(this, &UWidget_QuickSlot::SlotUpdated);
}

void UWidget_QuickSlot::SlotUpdated(EEquipCategory inCategory, int inSlotIdx)
{
	if (SlotCategory != inCategory || ActiveSlotIdx != inSlotIdx) return;

	APlayerController* playerController = GetOwningPlayer();
	if (!playerController) return;
	USlotComponent* slotComp = playerController->GetComponentByClass<USlotComponent>();
	if (!slotComp) return;

	switch (SlotCategory)
	{
	case EEquipCategory::None:
	{
		break;
	}
	case EEquipCategory::Weapon:
	{
		if (slotComp->WeaponSlots.IsValidIndex(inSlotIdx))
		{
			Image_Item->SetBrushFromTexture(slotComp->WeaponSlots[inSlotIdx].Icon);
		}
		break;
	}
	case EEquipCategory::Rune:
	{
		if (slotComp->RuneSlots.IsValidIndex(inSlotIdx))
		{
			Image_Item->SetBrushFromTexture(slotComp->RuneSlots[inSlotIdx].Icon);
		}
		break;
	}
	case EEquipCategory::FragmentOfGod:
	{
		break;
	}
	case EEquipCategory::UsableItem:
	{
		if (slotComp->UsableSlots.IsValidIndex(inSlotIdx))
		{
			Image_Item->SetBrushFromTexture(slotComp->UsableSlots[inSlotIdx].Icon);
		}
		break;
	}
	case EEquipCategory::Magic:
	{
		break;
	}
	default:
	{
		break;
	}
	}
}
