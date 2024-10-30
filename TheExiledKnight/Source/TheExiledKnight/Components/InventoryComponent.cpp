// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Subsystems/InventorySubsystem.h"

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

const TArray<FInventorySlot>& UInventoryComponent::GetContents(EItemCategory Category)
{
	return Inventory;
}

int UInventoryComponent::GetIndexToAdd(uint8 ID)
{
	for (int index = 0; index < Inventory_Size; index++)
	{
		if (Inventory[index].Item.ID == 1)
			return index;
		else if (Inventory[index].Item.ID > ID)
			return index;
	}

	return 0;
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
	UInventorySubsystem* InventorySubsystem = this->GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	ItemDB = InventorySubsystem->GetItemDB();

	FItemStruct* InitItem = ItemDB->FindRow<FItemStruct>(FName("Empty"), TEXT("Empty Item"));;

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
		indexToAdd = GetIndexToAdd(ItemToAdd.ID);

		FInventorySlot tmp1, tmp2 = Inventory[indexToAdd];
		Inventory[indexToAdd].Item = ItemToAdd;
		Inventory[indexToAdd].Amount = 1;

		for (int index = indexToAdd + 1; index < Inventory_Size; index++)
		{
			tmp1 = Inventory[index];
			Inventory[index] = tmp2;
			tmp2 = tmp1;
		}
		
		UE_LOG(LogTemp, Warning, TEXT("add new empty slot"));
	}

	return true;
}

