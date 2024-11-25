// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment/Widget_EquipSelect_ContentSlot.h"
#include "UI/Equipment/Widget_EquipSelectWindow.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/KismetTextLibrary.h"
#include "Components/SlotComponent.h"
#include "UI/UISubsystem.h"
#include "EKGameplayTags.h"

void UWidget_EquipSelect_ContentSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_EquipSelect_ContentSlot::UpdateSlot(EItemCategory inCategory, const FEKPlayerMagic& inData)
{
	Category = inCategory;
	MagicData = inData;

	Image_Item->SetBrushFromTexture(SlotData.Item.Icon);
}

void UWidget_EquipSelect_ContentSlot::UpdateSlot(EItemCategory inCategory, const FInventorySlot& inData)
{
	Category = inCategory;
	SlotData = inData;

	if (inData.Quantity > 0)
	{
		Image_Item->SetBrushFromTexture(SlotData.Item.Icon);

		Text_Quantity->SetText(UKismetTextLibrary::Conv_IntToText(inData.Quantity));
		Text_Quantity->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
		Text_Quantity->SetVisibility(ESlateVisibility::Collapsed);
}

void UWidget_EquipSelect_ContentSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	UUISubsystem* UISystem = GetWorld()->GetGameInstance()->GetSubsystem<UUISubsystem>();
	if (!UISystem) return;
	UUserWidget* widget = UISystem->GetWidget(FEKGameplayTags::Get().UI_Widget_GameMenu_EquipSelect);
	if (!widget) return;
	UWidget_EquipSelectWindow* EquipSelectWidget = Cast<UWidget_EquipSelectWindow>(widget);
	if (!EquipSelectWidget) return;

	switch (Category)
	{
	case EItemCategory::None:
		break;
	case EItemCategory::Weapon:
		EquipSelectWidget->UpdateDescription_Weapon(SlotData);
		break;
	case EItemCategory::Rune:
		EquipSelectWidget->UpdateDescription_Rune(SlotData);
		break;
	case EItemCategory::FragmentOfGod:
		break;
	case EItemCategory::UseableItem:
		EquipSelectWidget->UpdateDescription_Item(SlotData);
		break;
	case EItemCategory::Magic:
		EquipSelectWidget->UpdateDescription_Magic(MagicData);
		break;
	case EItemCategory::Upgrades:
		break;
	case EItemCategory::Hunting:
		break;
	default:
		break;
	}
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
		case EItemCategory::None:
		{
			break;
		}
		case EItemCategory::Weapon:
		{
			// Equip Weapon
			slotComp->EquipWeapon(SlotData.Item);
			break;
		}
		case EItemCategory::Rune:
		{
			// Equip Rune
			slotComp->EquipRune(SlotData.Item);
			break;
		}
		case EItemCategory::FragmentOfGod:
		{
			break;
		}
		case EItemCategory::UseableItem:
		{
			// Equip Useable Item
			slotComp->EquipUseableItem(SlotData.Item);
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
