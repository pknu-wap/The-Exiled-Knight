// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment/Widget_EquipSelectWindow.h"
#include "UI/Equipment/Widget_EquipSelect_ContentList.h"
#include "Components/TextBlock.h"

void UWidget_EquipSelectWindow::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_EquipSelectWindow::UpdateContents(EEquipCategory Category)
{
	switch (Category)
	{
	case EEquipCategory::None:
	{
		break;
	}
	case EEquipCategory::Weapon:
	{
		Text_Category->SetText(FText::FromString(FString("Weapon")));
		break;
	}
	case EEquipCategory::Rune:
	{
		Text_Category->SetText(FText::FromString(FString("Rune")));
		break;
	}
	case EEquipCategory::FragmentOfGod:
	{
		Text_Category->SetText(FText::FromString(FString("Fragment")));
		break;
	}
	case EEquipCategory::UsableItem:
	{
		Text_Category->SetText(FText::FromString(FString("Usable Item")));
		break;
	}
	default:
		break;
	}

	ContentList->UpdateContents(Category);
}
