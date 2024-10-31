// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/InventorySubsystem.h"

UInventorySubsystem::UInventorySubsystem()
{

}

void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ItemDB = LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/TheExiledKnight/Inventory/DataTables/DT_Item.DT_Item'"));

	if (ItemDB == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDB is null"));
		return;
	}

	uint8 ID = 0;

	for (auto RowName : ItemDB->GetRowNames())
	{
		ID++;
		FItemStruct* ItemInfo = ItemDB->FindRow<FItemStruct>(RowName, TEXT("GetItemRow"));
		if (ItemInfo != nullptr)
		{
			ItemDictionary.Add(ID, *ItemInfo);
		}
	}
}

FItemStruct* UInventorySubsystem::GetItemRow(FName RowName)
{
	return ItemDB->FindRow<FItemStruct>(RowName, TEXT("GetItemRow"));
}

FItemStruct* UInventorySubsystem::GetItemInfo(uint8 ID)
{
	FItemStruct* ItemInfo = ItemDictionary.Find(ID);

	if (ItemInfo == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetItemInfo : ItemInfo == nullptr"));
		return nullptr;
	}

	return ItemInfo;
}
