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

	for (FName RowName : ItemInfoDB->GetRowNames())
	{
		FItemStruct* ItemInfo = ItemInfoDB->FindRow<FItemStruct>(RowName, TEXT("GetItemRow"));
		if (ItemInfo != nullptr)
		{
			ItemDictionary.Add(ItemInfo->ID, *ItemInfo);
		}
	}

	// Item Object Dictionary Initialize

	ItemClassDB = LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/TheExiledKnight/Inventory/DataTables/ItemData/DT_ItemInfo.DT_ItemInfo'"));

	if (ItemClassDB == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemClassDB is null"));
		return;
	}

	WeaponDB = LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/TheExiledKnight/Inventory/DataTables/WeaponData/DT_WeaponInfo.DT_WeaponInfo'"));

	if (WeaponDB == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponDB is null"));
		return;
	}
	
	TArray<FName> WeaponNames = WeaponDB->GetRowNames();

	for (FName RowName : WeaponNames)
	{
		FWeaponStruct* WeaponInfo = WeaponDB->FindRow<FWeaponStruct>(RowName, TEXT("GetItemRow"));
		if (WeaponInfo != nullptr)
		{
			WeaponDictionary.Add(WeaponInfo->ID, *WeaponInfo);
		}
	}

	RuneDB = LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/TheExiledKnight/Inventory/DataTables/RuneData/DT_RuneInfo.DT_RuneInfo'"));

	if (RuneDB == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("RuneDB is null"));
		return;
	}

	TArray<FName> RuneNames = RuneDB->GetRowNames();

	for (FName RowName : RuneNames)
	{
		FRune* runeInfo = RuneDB->FindRow<FRune>(RowName, TEXT("GetItemRow"));
		if (runeInfo != nullptr)
		{
			RuneDictionary.Add(runeInfo->ID, *runeInfo);
		}
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

FWeaponStruct* UInventorySubsystem::GetWeaponInfo(uint8 ID)
{
	FWeaponStruct* weaponInfo = WeaponDictionary.Find(ID);

	if (weaponInfo == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetWeaponInfo : weaponInfo == nullptr"));
		return nullptr;
	}

	return weaponInfo;
}

FRune* UInventorySubsystem::GetRuneInfo(uint8 ID)
{
	FRune* runeInfo = RuneDictionary.Find(ID);

	if (runeInfo == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetRuneInfo : runeInfo == nullptr"));
		return nullptr;
	}

	return runeInfo;
}
