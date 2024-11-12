// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/Widget_Inventory.h"
#include "UI/Inventory/Widget_InvContentList.h"
#include "UI/Inventory/Widget_Inventory_CategorySlot.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"

void UWidget_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	CategorySlots.Empty();
	TArray<UWidget*> childrens = ScrollBox_Category->GetAllChildren();
	for (int i = 0; i < childrens.Num(); i++)
	{
		UWidget_Inventory_CategorySlot* CategorySlot = 
			Cast<UWidget_Inventory_CategorySlot>(childrens[i]);
		if (CategorySlot)
		{
			CategorySlots.Add(CategorySlot);
		}
	}

	Button_BeforeCategory->OnClicked.Clear();
	Button_BeforeCategory->OnClicked.AddDynamic(this, &UWidget_Inventory::ShowBeforeCategory);
	Button_NextCategory->OnClicked.Clear();
	Button_NextCategory->OnClicked.AddDynamic(this, &UWidget_Inventory::ShowNextCategory);

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, [&]() {
		UpdateContents(EItemCategory::Weapon);
		}, 0.25, false);
}

void UWidget_Inventory::UpdateContents(EItemCategory Category)
{
	for (int i = 0; i < CategorySlots.Num(); i++)
	{
		if (CategorySlots[i]->Category == Category)
		{
			CategorySlots[i]->Hover();
		}
		else
			CategorySlots[i]->UnHover();
	}

	ContentList->UpdateContents(Category);
}

void UWidget_Inventory::ShowBeforeCategory()
{
	if (CurrentCategoryIdx - 1 >= 0)
	{
		CurrentCategoryIdx--;

		ScrollBox_Category->ScrollWidgetIntoView(CategorySlots[CurrentCategoryIdx]);
		UpdateContents(CategorySlots[CurrentCategoryIdx]->Category);
	}
}

void UWidget_Inventory::ShowNextCategory()
{
	if (CurrentCategoryIdx + 1 < CategorySlots.Num())
	{
		CurrentCategoryIdx++;

		ScrollBox_Category->ScrollWidgetIntoView(CategorySlots[CurrentCategoryIdx]);
		UpdateContents(CategorySlots[CurrentCategoryIdx]->Category);
	}
}
