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

void UWidget_QuickSlot::SlotUpdated(EItemCategory inCategory, int inSlotIdx)
{
	if (SlotCategory != inCategory || ActiveSlotIdx != inSlotIdx)
	{
		Image_Item->SetOpacity(0);
		return;
	}

	APlayerController* playerController = GetOwningPlayer();
	if (!playerController) return;
	USlotComponent* slotComp = playerController->GetComponentByClass<USlotComponent>();
	if (!slotComp) return;

	switch (SlotCategory)
	{
	case EItemCategory::None:
	{
		break;
	}
	case EItemCategory::Weapon:
	{
		if (slotComp->WeaponSlots.IsValidIndex(inSlotIdx))
		{
			Image_Item->SetBrushFromTexture(slotComp->WeaponSlots[inSlotIdx].Icon);
			Image_Item->SetOpacity(1);
		}
		break;
	}
	case EItemCategory::Rune:
	{
		if (slotComp->RuneSlots.IsValidIndex(inSlotIdx))
		{
			Image_Item->SetBrushFromTexture(slotComp->RuneSlots[inSlotIdx].Icon);
			Image_Item->SetOpacity(1);
		}
		break;
	}
	case EItemCategory::FragmentOfGod:
	{
		break;
	}
	case EItemCategory::UseableItem:
	{
		if (slotComp->UsableSlots.IsValidIndex(inSlotIdx))
		{
			Image_Item->SetBrushFromTexture(slotComp->UsableSlots[inSlotIdx].Icon);
			Image_Item->SetOpacity(1);
		}
		break;
	}
	case EItemCategory::Magic:
	{
		break;
	}
	default:
	{
		break;
	}
	}
}