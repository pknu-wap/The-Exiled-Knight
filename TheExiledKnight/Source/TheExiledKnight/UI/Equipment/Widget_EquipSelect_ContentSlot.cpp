// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment/Widget_EquipSelect_ContentSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/KismetTextLibrary.h"
#include "Components/SlotComponent.h"

void UWidget_EquipSelect_ContentSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_EquipSelect_ContentSlot::UpdateSlot(EEquipCategory inCategory, const FInventorySlot& inData)
{
	Category = inCategory;
	SlotData = inData;

	Image_Item->SetBrushFromTexture(SlotData.Item.Icon);
	if (inData.Amount > 0)
	{
		Text_Quantity->SetText(UKismetTextLibrary::Conv_IntToText(inData.Amount));
		Text_Quantity->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
		Text_Quantity->SetVisibility(ESlateVisibility::Collapsed);
}

FEventReply UWidget_EquipSelect_ContentSlot::RedirectMouseDownToWidget(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (SlotData.Item.ID == 0) return Reply;

	APlayerController* controller = GetOwningPlayer();
	if (!controller) return Reply;
	USlotComponent* slotComp = controller->GetComponentByClass<USlotComponent>();
	if (!slotComp) return Reply;

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
	{
		// Equip Item
		switch (Category)
		{
		case EEquipCategory::None:
		{
			break;
		}
		case EEquipCategory::Weapon:
		{
			// Equip Weapon
			slotComp->EquipWeapon(SlotData.Item);
			break;
		}
		case EEquipCategory::Rune:
		{
			// Equip Rune
			slotComp->EquipRune(SlotData.Item);
			break;
		}
		case EEquipCategory::FragmentOfGod:
		{


			break;
		}
		case EEquipCategory::UsableItem:
		{
			// Equip Usable Item
			slotComp->EquipUsableItem(SlotData.Item);
			break;
		}
		default:
		{

			break;
		}
		}

	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true)
	{
		// UnEquip Item
	}

	return Reply;
}
