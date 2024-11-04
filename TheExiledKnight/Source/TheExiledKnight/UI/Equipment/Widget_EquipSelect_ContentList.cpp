// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment/Widget_EquipSelect_ContentList.h"
#include "UI/Equipment/EquipSelect_ListData.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/InventoryComponent.h"

void UWidget_EquipSelect_ContentList::UpdateContents(EEquipCategory Category)
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (!player) return;
	UInventoryComponent* inventoryComp = player->GetComponentByClass<UInventoryComponent>();
	if (!inventoryComp) return;

	ContentList->ClearListItems();
	
	const TArray<FInventorySlot>& contents = inventoryComp->GetContents(Category);
	for (int i = 0; i < contents.Num(); i += 5)
	{
		UEquipSelect_ListData* data = NewObject<UEquipSelect_ListData>(UEquipSelect_ListData::StaticClass());
		data->Category = Category;

		for (int j = i; j < j + 5; j++)
		{
			if (contents.IsValidIndex(j))
			{
				data->Items.Add(contents[j]);
			}
		}

		ContentList->AddItem(data);
	}
}
