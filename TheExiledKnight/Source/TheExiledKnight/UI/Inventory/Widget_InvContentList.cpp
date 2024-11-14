// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/Widget_InvContentList.h"
#include "UI/Inventory/Inventory_ListData.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/InventoryComponent.h"

void UWidget_InvContentList::UpdateContents(EItemCategory Category)
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (!player) return;
	UInventoryComponent* inventoryComp = player->GetComponentByClass<UInventoryComponent>();
	if (!inventoryComp) return;

	const TArray<FInventorySlot>& contents = inventoryComp->GetConstContents(Category);
	for (int i = 0; i < contents.Num(); i += 5)
	{
		UInventory_ListData* data = NewObject<UInventory_ListData>(UInventory_ListData::StaticClass());

		for (int j = i; j < j + 5; j++)
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
