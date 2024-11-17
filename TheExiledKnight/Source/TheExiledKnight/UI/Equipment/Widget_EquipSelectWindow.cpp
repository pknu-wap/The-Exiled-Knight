// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment/Widget_EquipSelectWindow.h"
#include "UI/Equipment/Widget_EquipSelect_ContentList.h"
#include "Components/TextBlock.h"

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
		Text_Category->SetText(FText::FromString(FString("Weapon")));
		break;
	}
	case EItemCategory::Rune:
	{
		Text_Category->SetText(FText::FromString(FString("Rune")));
		break;
	}
	case EItemCategory::FragmentOfGod:
	{
		Text_Category->SetText(FText::FromString(FString("Fragment")));
		break;
	}
	case EItemCategory::UseableItem:
	{
		Text_Category->SetText(FText::FromString(FString("Usable Item")));
		break;
	}
	default:
		break;
	}

	ContentList->UpdateContents(Category);
}
