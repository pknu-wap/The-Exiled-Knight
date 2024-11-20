// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Upgrade/Equipment/Widget_UpgradeEquipment.h"
#include "UI/Upgrade/Equipment/Widget_EU_CategorySlot.h"
#include "UI/Inventory/Widget_InvContentList.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/InventoryComponent.h"

void UWidget_UpgradeEquipment::NativeConstruct()
{
	Super::NativeConstruct();

	CategorySlots.Empty();
	TArray<UWidget*> childrens = ScrollBox_Category->GetAllChildren();
	for (int i = 0; i < childrens.Num(); i++)
	{
		UWidget_EU_CategorySlot* CategorySlot =
			Cast<UWidget_EU_CategorySlot>(childrens[i]);
		if (CategorySlot)
		{
			CategorySlots.Add(CategorySlot);
		}
	}

	Button_BeforeCategory->OnClicked.Clear();
	Button_BeforeCategory->OnClicked.AddDynamic(this, &UWidget_UpgradeEquipment::ShowBeforeCategory);
	Button_NextCategory->OnClicked.Clear();
	Button_NextCategory->OnClicked.AddDynamic(this, &UWidget_UpgradeEquipment::ShowNextCategory);

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, [&]() {
		UpdateContents(EUpgradeItemType::Sword);
		}, 0.25, false);
}

void UWidget_UpgradeEquipment::UpdateContents(EUpgradeItemType Category)
{
	CurrentType = Category;

	for (int i = 0; i < CategorySlots.Num(); i++)
	{
		if (CategorySlots[i]->Category == Category)
		{
			CategorySlots[i]->Hover();
		}
		else
			CategorySlots[i]->UnHover();
	}

	ContentList->UpdateUpgradeContents(Category);
}

void UWidget_UpgradeEquipment::LevelUp_Equipment(const FItemStruct& InItem)
{
	APlayerController* pc = GetOwningPlayer();
	if (!pc) return;
	UInventoryComponent* inventory = pc->GetComponentByClass<UInventoryComponent>();
	if (!inventory) return;
	inventory->UpgradeItem(InItem);

	ContentList->UpdateUpgradeContents(CurrentType);

	// inventory->GetContents(CurrentType);S
}

void UWidget_UpgradeEquipment::ShowBeforeCategory()
{
	if (CurrentCategoryIdx - 1 >= 0)
	{
		CurrentCategoryIdx--;

		ScrollBox_Category->ScrollWidgetIntoView(CategorySlots[CurrentCategoryIdx]);
		UpdateContents(CategorySlots[CurrentCategoryIdx]->Category);
	}
}

void UWidget_UpgradeEquipment::ShowNextCategory()
{
	if (CurrentCategoryIdx + 1 < CategorySlots.Num())
	{
		CurrentCategoryIdx++;

		ScrollBox_Category->ScrollWidgetIntoView(CategorySlots[CurrentCategoryIdx]);
		UpdateContents(CategorySlots[CurrentCategoryIdx]->Category);
	}
}
