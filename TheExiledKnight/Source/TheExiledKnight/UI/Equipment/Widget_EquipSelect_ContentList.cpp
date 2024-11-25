// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment/Widget_EquipSelect_ContentList.h"
#include "UI/Equipment/EquipSelect_ListData.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/InventoryComponent.h"

void UWidget_EquipSelect_ContentList::UpdateContents(EItemCategory Category)
{
	APlayerController* playerController = GetOwningPlayer();
	if (!playerController) return;
	UInventoryComponent* inventoryComp = playerController->GetComponentByClass<UInventoryComponent>();
	if (!inventoryComp) return;

	ContentList->ClearListItems();
	
	if (Category == EItemCategory::Magic)
	{
		const TArray<FEKPlayerMagic>& Magics = inventoryComp->GetMagics();
		for (int i = 0; i < Magics.Num(); i += 5)
		{
			UEquipSelect_ListData* data = NewObject<UEquipSelect_ListData>(UEquipSelect_ListData::StaticClass());
			data->Category = Category;

			for (int j = i; j < i + 5; j++)
			{
				if (Magics.IsValidIndex(j))
				{
					data->Magics.Add(Magics[j]);
				}
				else
					UE_LOG(LogTemp, Warning, TEXT("Widget_InvContentList"))
			}

			ContentList->AddItem(data);
		}
	}
	else
	{
		const TArray<FInventorySlot>& contents = inventoryComp->GetConstContents(Category);

		for (int i = 0; i < contents.Num(); i += 5)
		{
			UEquipSelect_ListData* data = NewObject<UEquipSelect_ListData>(UEquipSelect_ListData::StaticClass());
			data->Category = Category;

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
}
