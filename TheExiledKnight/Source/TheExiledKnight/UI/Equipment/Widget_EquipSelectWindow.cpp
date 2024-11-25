// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment/Widget_EquipSelectWindow.h"
#include "UI/Equipment/Widget_EquipSelect_ContentList.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Components/WidgetSwitcher.h"

void UWidget_EquipSelectWindow::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_EquipSelectWindow::UpdateContents(EItemCategory Category)
{
	switch (Category)
	{
	case EItemCategory::None:
	{
		break;
	}
	case EItemCategory::Weapon:
	{
		WidgetSwitcher->SetActiveWidget(Overlay_Weapon);
		Text_Category->SetText(FText::FromString(FString("Weapon")));
		break;
	}
	case EItemCategory::Rune:
	{
		WidgetSwitcher->SetActiveWidget(Overlay_Rune);
		Text_Category->SetText(FText::FromString(FString("Rune")));
		break;
	}
	case EItemCategory::FragmentOfGod:
	{
		WidgetSwitcher->SetActiveWidget(Overlay_Fragment);
		Text_Category->SetText(FText::FromString(FString("Fragment")));
		break;
	}
	case EItemCategory::UseableItem:
	{
		WidgetSwitcher->SetActiveWidget(Overlay_Item);
		Text_Category->SetText(FText::FromString(FString("Usable Item")));
		break;
	}
	case EItemCategory::Magic:
	{
		WidgetSwitcher->SetActiveWidget(Overlay_Magic);
		Text_Category->SetText(FText::FromString(FString("Magic")));
		break;
	}
	default:
		break;
	}

	ContentList->UpdateContents(Category);
}
