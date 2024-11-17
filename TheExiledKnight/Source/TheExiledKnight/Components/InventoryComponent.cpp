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

const TArray<FInventorySlot>& UInventoryComponent::GetConstInventory(EItemCategory Category)
{
	switch (Category)
	{
	case EItemCategory::Weapon:
		return Weapon;
	case EItemCategory::Fragment:
		return Fragment;
	case EItemCategory::Hunting:
		return Hunting;
	case EItemCategory::Upgrades:
		return Upgrades;
	case EItemCategory::Rune:
		return Rune;
	default:
		return None;
	}
}

int UInventoryComponent::GetIndexToAdd(uint8 ID, EItemCategory Category)
{
	const TArray<FInventorySlot>& Slots = GetConstInventory(Category);

	for (int index = 0; index < Slots.Num(); index++)
	{
		if (Slots[index].Item.ID == 1)
			return index;
		else if (Slots[index].Item.ID > ID)
			return index;
	}

	return -1;
}

int UInventoryComponent::GetDupSlotIndex(uint8 ID, EItemCategory Category)
{
	const TArray<FInventorySlot>& Slots = GetConstInventory(Category);

	for (int index = 0; index < Slots.Num(); index++)
	{
		if (Slots[index].Item.ID == ID)
			return index;
	}

	return -1;
}

int UInventoryComponent::GetEmptySlotIndex(EItemCategory Category)
{
	const TArray<FInventorySlot>& Slots = GetConstInventory(Category);

	for (int index = 0; index < Slots.Num(); index++)
	{
		if (Slots[index].Item.ID == 1)
			return index;
	}

	return -1;
}

void UInventoryComponent::InitializeInventory()
{
	AddNewSlot(GetInventory(EItemCategory::None));
	AddNewSlot(GetInventory(EItemCategory::Weapon));
	AddNewSlot(GetInventory(EItemCategory::Fragment));
	AddNewSlot(GetInventory(EItemCategory::Hunting));
	AddNewSlot(GetInventory(EItemCategory::Upgrades));
	AddNewSlot(GetInventory(EItemCategory::Rune));

	UE_LOG(LogTemp, Warning, TEXT("InitializeInventory"))
}

TArray<FInventorySlot>& UInventoryComponent::GetInventory(EItemCategory Category)
{
	switch (Category)
	{
	case EItemCategory::Weapon:
		return Weapon;
	case EItemCategory::Fragment:
		return Fragment;
	case EItemCategory::Hunting:
		return Hunting;
	case EItemCategory::Upgrades:
		return Upgrades;
	case EItemCategory::Rune:
		return Rune;
	default:
		return None;
	}
}

bool UInventoryComponent::AddItem(FItemStruct ItemToAdd, int Quantity)
{
	TArray<FInventorySlot>& Slots = GetInventory(ItemToAdd.ItemCategory);

	int indexToAdd = GetDupSlotIndex(ItemToAdd.ID, ItemToAdd.ItemCategory);

	if (indexToAdd != -1) // if there are duplicate items
	{
		if (Slots[indexToAdd].Quantity + Quantity > Slots[indexToAdd].Item.MaxStackSize)
		{
			Slots[indexToAdd].Quantity = ItemToAdd.MaxStackSize;
			UE_LOG(LogTemp, Warning, TEXT("This Slot is full"));
		}
		else
		{
			Slots[indexToAdd].Quantity += Quantity;
			UE_LOG(LogTemp, Warning, TEXT("Quantity++"));
		}

		return true;
	}

	indexToAdd = GetEmptySlotIndex(ItemToAdd.ItemCategory);

	if (indexToAdd == -1) // if inventory is full
	{
		// extand inventory
		UE_LOG(LogTemp, Warning, TEXT("Expand Inventory Slot"));

		AddNewSlot(Slots);
	}

	// if empty slot exists
	// Sort
	indexToAdd = GetIndexToAdd(ItemToAdd.ID, ItemToAdd.ItemCategory);

	if (indexToAdd == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetIndexToAdd returns -1"))
		return false;
	}

	FInventorySlot tmp1, tmp2 = Slots[indexToAdd];
	Slots[indexToAdd].Item = ItemToAdd;
	Slots[indexToAdd].Quantity = Quantity;

	for (int index = indexToAdd + 1; index < Slots.Num(); index++)
	{
		tmp1 = Slots[index];
		Slots[index] = tmp2;
		tmp2 = tmp1;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Add new Item to Inventory Slot"));

	return true;
}

bool UInventoryComponent::UseItem(FItemStruct ItemToUse, int Quantity)
{
	if (!ItemToUse.bUseable)
		return false;

	TArray<FInventorySlot>& Slots = GetInventory(ItemToUse.ItemCategory);

	int index = GetDupSlotIndex(ItemToUse.ID, ItemToUse.ItemCategory);

	if (index == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("You don't have that item."));
		return false;
	}

	if (Slots[index].Quantity < Quantity)
		return false;
	
	AEKItem_Base* ItemInstance = GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>()->GetOrCreateItemInstance(ItemToUse.Name);
	if (ItemInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UseItem : ItemInstance is nullptr"));
		return false;
	}

	ItemInstance->UseItem();

	Slots[index].Item;
	Slots[index].Quantity -= Quantity;

	if (Slots[index].Quantity == 0)
		DeleteItem(ItemToUse);

	return true;
}

bool UInventoryComponent::DeleteItem(FItemStruct ItemToDelete, int Quantity)
{
	TArray<FInventorySlot>& Slots = GetInventory(ItemToDelete.ItemCategory);

	int index = GetDupSlotIndex(ItemToDelete.ID, ItemToDelete.ItemCategory);

	Slots[index].Quantity -= Quantity;

	if (Slots[index].Quantity <= 0 && Slots[index].Item.bDestroyable)
	{
		Slots[index] = FInventorySlot();

		FInventorySlot tmp1, tmp2 = Slots[index + 1];

		for (index; index < Slots.Num(); index++)
		{
			tmp1 = Slots[index];
			Slots[index] = tmp2;
			tmp2 = tmp1;
		}
		
		UE_LOG(LogTemp, Warning, TEXT("add new empty slot"));
	}

	return true;
}

bool UInventoryComponent::DeleteSlots(TArray<FInventorySlot>& Slots)
{
	if (Slots.Num() <= ExpansionSize)
		return false;

	int EmptySlotCnt = 0;

	for (int i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i].Item.ID == 1)
			EmptySlotCnt++;
	}

	int IterCnt = EmptySlotCnt / ExpansionSize;
	int IndexToDelete = Slots.Num() - (IterCnt * ExpansionSize);

	for (int i = 0; i < IterCnt; i++)
	{
		Slots.RemoveAt(IndexToDelete);
	}

	return true;
}

bool UInventoryComponent::AddNewSlot(TArray<FInventorySlot>& Slots)
{
	UE_LOG(LogTemp, Warning, TEXT("AddNewSlot"))
	Slots.AddDefaulted(ExpansionSize);

	return true;
}

