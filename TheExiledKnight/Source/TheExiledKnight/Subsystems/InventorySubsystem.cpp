// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/InventorySubsystem.h"

UInventorySubsystem::UInventorySubsystem()
{

}

void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ItemInfoDB = LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/TheExiledKnight/Inventory/DataTables/DT_Item.DT_Item'"));

	if (ItemInfoDB == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDB is null"));
		return;
	}

	uint8 ID = 0;

	for (FName RowName : ItemInfoDB->GetRowNames())
	{
		ID++;
		FItemStruct* ItemInfo = ItemInfoDB->FindRow<FItemStruct>(RowName, TEXT("GetItemRow"));
		if (ItemInfo != nullptr)
		{
			ItemDictionary.Add(ID, *ItemInfo);
		}
	}

	// Item Object Dictionary Initialize

	ItemClassDB = LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/TheExiledKnight/Inventory/DataTables/DT_ItemClass.DT_ItemClass'"));

	if (ItemClassDB == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemClassDB is null"));
		return;
	}
}

const FItemStruct* UInventorySubsystem::GetItemInfo(uint8 ID)
{
	FItemStruct* ItemInfo = ItemDictionary.Find(ID);

	if (ItemInfo == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetItemInfo : ItemInfo == nullptr"));
		return nullptr;
	}

	return ItemInfo;
}

AEKItem_Base* UInventorySubsystem::GetOrCreateItemInstance(FName ItemName)
{
	AEKItem_Base* ItemInstance;

	if (!ItemInstanceCache.Contains(ItemName))
	{
		UE_LOG(LogTemp, Warning, TEXT("GetOrCreateItemInstance : ItemInstanceCache doesn't exist"));

		// add cache
		ItemInstance = NewObject<AEKItem_Base>(this, GetItemClass(ItemName));

		if (ItemInstance == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("GetOrCreateItemInstance : ItemInstance is nullptr"));
			return nullptr;
		}


		ItemInstanceCache.Add(ItemName, ItemInstance);

		return ItemInstance;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetOrCreateItemInstance : ItemInstanceCache exists"));
		ItemInstance = *ItemInstanceCache.Find(ItemName);
		return ItemInstance;
	}
}

const TSubclassOf<AEKItem_Base> UInventorySubsystem::GetItemClass(FName ItemName)
{
	if (ItemClassDB == nullptr)
		return nullptr;

	FItemObject* ItemObject = ItemClassDB->FindRow<FItemObject>(ItemName, TEXT("GetItemRow"));

	if (ItemObject == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetItemInfo : ItemInfo == nullptr"));
		return nullptr;
	}

	return ItemObject->ItemObject;
}
