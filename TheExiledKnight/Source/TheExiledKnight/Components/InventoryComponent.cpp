// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeInventory();
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::SortInventory()
{
	/*
	카테고리별로 우선 구분하고
	그 다음 id로 구분
	*/
}

int UInventoryComponent::GetIndexToAdd(EItemCategory Category, uint8 ID)
{
	for (int index = 0; index < Inventory_Size; index++)
	{
		if (Inventory[index].Item.ItemCategory < Category)
			return index;
		else if (Inventory[index].Item.ItemCategory == Category && Inventory[index].Item.ID < ID)
			return index;
	}

	return -1;
}

int UInventoryComponent::GetDupSlotIndex(uint8 ID, int MaxStackSize)
{
	for (int index = 0; index < Inventory_Size; index++)
	{
		if (Inventory[index].Item.ID == ID && Inventory[index].Amount != MaxStackSize)
			return index;
	}

	return -1;
}

int UInventoryComponent::GetEmptySlotIndex()
{
	for (int index = 0; index < Inventory_Size; index++)
	{
		if (Inventory[index].Item.ID == 1)
			return index;
	}

	return -1;
}

void UInventoryComponent::InitializeInventory()
{
	ItemDB = LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/TheExiledKnight/Inventory/DataTables/DT_Item.DT_Item'"));

	FItemStruct* InitItem;
	InitItem = ItemDB->FindRow<FItemStruct>(FName("Empty"), TEXT("Empty Item"));

	for (int i = 0; i < Inventory_Size; i++)
	{
		FInventorySlot item;
		item.Amount = 0;
		item.Item = *InitItem;
		Inventory.Add(item);
	}
}

bool UInventoryComponent::AddItem(FItemStruct ItemToAdd)
{
	if (!ItemDB)
		return false;

	// Sort

	int indexToAdd = GetDupSlotIndex(ItemToAdd.ID, ItemToAdd.MaxStackSize);

	if (indexToAdd != -1) // if there are duplicate items
	{
		Inventory[indexToAdd].Amount++;
		return true;
	}

	indexToAdd = GetEmptySlotIndex();

	if (indexToAdd == -1) // if inventory is full
	{
		UE_LOG(LogTemp, Warning, TEXT("full"));
		return false;
	}
	else // if empty slot exists
	{
		// Sort
		//indexToAdd = GetIndexToAdd(ItemToAdd.ItemCategory, ItemToAdd.ID);

		//FInventorySlot temp = Inventory[indexToAdd];

		//for (int index = indexToAdd; index < Inventory_Size - 1; index++)
		//{
		//	Inventory[index] = Inventory[index + 1];
		//	temp = Inventory[index + 1];
		//}
		
		Inventory[indexToAdd].Item = ItemToAdd;
		Inventory[indexToAdd].Amount++;
		UE_LOG(LogTemp, Warning, TEXT("add new empty slot"));
	}

	return true;
}

