// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/Widget_InvContentList.h"
#include "UI/Inventory/Inventory_ListData.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/InventoryComponent.h"

void UWidget_InvContentList::UpdateContents(EItemCategory Category)
{
	APlayerController* playerController = GetOwningPlayer();
	if (!playerController) return;
	UInventoryComponent* inventoryComp = playerController->GetComponentByClass<UInventoryComponent>();
	if (!inventoryComp) return;


	const TArray<FInventorySlot>& contents = inventoryComp->GetConstInventory(Category);

	ContentList->ClearListItems();

	//const TArray<FInventorySlot>& contents = inventoryComp->GetInventory(Category);

	for (int i = 0; i < contents.Num(); i += 5)
	{
		UInventory_ListData* data = NewObject<UInventory_ListData>(UInventory_ListData::StaticClass());
		data->StartIdx = i;

		for (int j = i; j < i + 5; j++)
		{
			if (contents.IsValidIndex(j))
			{
				data->Items.Add(contents[j]);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("Widget_InvContentList"))
		}

		ContentList->AddItem(data);
	}
}
