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

	ItemClassDB = LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/TheExiledKnight/Inventory/DataTables/ItemData/DT_ItemClass.DT_ItemClass'"));

	if (ItemClassDB == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemClassDB is null"));
		return;
	}

	for (FName RowName : ItemClassDB->GetRowNames())
	{
		FItemObject* ItemClassInfo = ItemClassDB->FindRow<FItemObject>(RowName, TEXT("GetItemRow"));
		if (ItemClassInfo != nullptr)
		{
			ItemInstanceDictionary.Add(ItemClassInfo->ID, ItemClassInfo->ItemObject);
		}
	}

	LevelRateDB = LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/TheExiledKnight/Inventory/DataTables/DT_LevelRate.DT_LevelRate'"));

	if (LevelRateDB == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelRateDB is null"));
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

AEKItem_Base* UInventorySubsystem::CreateItemInstance(uint8 ID)
{
	AEKItem_Base* ItemInstance = NewObject<AEKItem_Base>(this, *ItemInstanceDictionary.Find(ID));

	return ItemInstance;
}

FLevelRate* UInventorySubsystem::GetLevelRateInfo(int level)
{
	if (LevelRateDB == nullptr)
		return nullptr;

	FName fnameLevel = FName(*FString::FromInt(level));

	FLevelRate* levelInfo = LevelRateDB->FindRow<FLevelRate>(fnameLevel, TEXT("GetItemRow"));

	if (levelInfo == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetItemInfo : ItemInfo == nullptr"));
		return nullptr;
	}

	return levelInfo;
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
