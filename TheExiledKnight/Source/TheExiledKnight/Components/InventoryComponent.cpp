// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Subsystems/InventorySubsystem.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent() called"));
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	None.Empty();
	Weapon.Empty();
	Rune.Empty();
	FragmentOfGod.Empty();
	UseableItem.Empty();
	Magic.Empty();
	Upgrades.Empty();
	Hunting.Empty();

	InitializeInventory();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

const TArray<FInventorySlot> UInventoryComponent::GetContents(EUpgradeItemType Category)
{
	switch (Category)
	{
	case EUpgradeItemType::Sword:
		break;
	case EUpgradeItemType::Spear:
		break;
	case EUpgradeItemType::Staff:
		break;
	case EUpgradeItemType::Potion:
		break;
	default:
		return Weapon;
		break;
	}

	return Weapon;
}

const TArray<FInventorySlot>& UInventoryComponent::GetConstContents(EItemCategory Category)
{
	switch (Category)
	{
	case EItemCategory::Weapon:
		return Weapon;
	case EItemCategory::Rune:
		return Rune;
	case EItemCategory::FragmentOfGod:
		return FragmentOfGod;
	case EItemCategory::UseableItem:
		return UseableItem;
	case EItemCategory::Magic:
		return Magic;
	case EItemCategory::Upgrades:
		return Upgrades;
	case EItemCategory::Hunting:
		return Hunting;
	default:
		return None;
	}
}

int UInventoryComponent::GetIndexToAdd(uint8 ID, EItemCategory Category)
{
	const TArray<FInventorySlot>& slots = GetConstContents(Category);

	for (int index = 0; index < slots.Num(); index++)
	{
		if (slots[index].Item.ID == 1)
			return index;
		else if (slots[index].Item.ID > ID)
			return index;
	}

	return -1;
}

int UInventoryComponent::GetItemIndex(uint8 ID, EItemCategory Category)
{
	const TArray<FInventorySlot>& slots = GetConstContents(Category);

	for (int index = 0; index < slots.Num(); index++)
	{
		if (slots[index].Item.ID == ID)
			return index;
	}

	return -1;
}

int UInventoryComponent::GetEmptySlotIndex(EItemCategory Category)
{
	const TArray<FInventorySlot>& slots = GetConstContents(Category);

	for (int index = 0; index < slots.Num(); index++)
	{
		if (slots[index].Item.ID == 1)
			return index;
	}

	return -1;
}

void UInventoryComponent::InitializeInventory()
{
	AddNewSlot(GetContents(EItemCategory::None));
	AddNewSlot(GetContents(EItemCategory::Weapon));
	AddNewSlot(GetContents(EItemCategory::Rune));
	AddNewSlot(GetContents(EItemCategory::FragmentOfGod));
	AddNewSlot(GetContents(EItemCategory::UseableItem));
	AddNewSlot(GetContents(EItemCategory::Magic));
	AddNewSlot(GetContents(EItemCategory::Upgrades));
	AddNewSlot(GetContents(EItemCategory::Hunting));

	UE_LOG(LogTemp, Warning, TEXT("InitializeInventory"))
}

TArray<FInventorySlot>& UInventoryComponent::GetContents(EItemCategory Category)
{
	switch (Category)
	{
	case EItemCategory::Weapon:
		return Weapon;
	case EItemCategory::Rune:
		return Rune;
	case EItemCategory::FragmentOfGod:
		return FragmentOfGod;
	case EItemCategory::UseableItem:
		return UseableItem;
	case EItemCategory::Magic:
		return Magic;
	case EItemCategory::Upgrades:
		return Upgrades;
	case EItemCategory::Hunting:
		return Hunting;
	default:
		return None;
	}
}

bool UInventoryComponent::AddItem(FItemStruct ItemToAdd, int Quantity)
{
	TArray<FInventorySlot>& slots = GetContents(ItemToAdd.ItemCategory);

	int indexToAdd = GetItemIndex(ItemToAdd.ID, ItemToAdd.ItemCategory);

	if (indexToAdd != -1) // if there are duplicate items
	{
		if (slots[indexToAdd].Quantity + Quantity > slots[indexToAdd].Item.MaxStackSize)
		{
			slots[indexToAdd].Quantity = ItemToAdd.MaxStackSize;
			UE_LOG(LogTemp, Warning, TEXT("This Slot is full"));
		}
		else
		{
			slots[indexToAdd].Quantity += Quantity;
			UE_LOG(LogTemp, Warning, TEXT("Quantity++"));
			AddItemDelegate.Broadcast();
		}

		return true;
	}

	indexToAdd = GetEmptySlotIndex(ItemToAdd.ItemCategory);

	if (indexToAdd == -1) // if inventory is full
	{
		// extand inventory
		UE_LOG(LogTemp, Warning, TEXT("Expand Inventory Slot"));

		AddNewSlot(slots);
	}

	// if empty slot exists
	// Sort
	indexToAdd = GetIndexToAdd(ItemToAdd.ID, ItemToAdd.ItemCategory);

	if (indexToAdd == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetIndexToAdd returns -1"))
		return false;
	}

	FInventorySlot tmp1, tmp2 = slots[indexToAdd];
	slots[indexToAdd].Item = ItemToAdd;
	slots[indexToAdd].Quantity = Quantity;

	for (int index = indexToAdd + 1; index < slots.Num(); index++)
	{
		if (slots[index].Item.ID == 1)
			break;

		tmp1 = slots[index];
		slots[index] = tmp2;
		tmp2 = tmp1;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Add new Item to Inventory Slot"));

	AddItemDelegate.Broadcast();

	return true;
}

bool UInventoryComponent::UseItem(FItemStruct ItemToUse, int Quantity)
{
	if (!ItemToUse.bUseable)
		return false;

	TArray<FInventorySlot>& slots = GetContents(ItemToUse.ItemCategory);

	int index = GetItemIndex(ItemToUse.ID, ItemToUse.ItemCategory);

	if (index == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("You don't have that item."));
		return false;
	}

	if (slots[index].Quantity < Quantity)
		return false;
	
	AEKItem_Base* ItemInstance = GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>()->GetOrCreateItemInstance(ItemToUse.Name);
	if (ItemInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UseItem : ItemInstance is nullptr"));
		return false;
	}

	ItemInstance->UseItem();

	DeleteItem(ItemToUse, Quantity);

	//Slots[index].Item;
	//Slots[index].Quantity -= Quantity;

	//if (Slots[index].Quantity == 0)
	//	DeleteItem(ItemToUse);

	return true;
}

bool UInventoryComponent::UpgradeItem(FItemStruct ItemToUpgrade, int MaterialCount)
{
	if (ItemToUpgrade.ItemLevel > 10)
		return false;

	TArray<FInventorySlot>& slots = GetContents(ItemToUpgrade.ItemCategory);

	int index = GetItemIndex(ItemToUpgrade.ID, ItemToUpgrade.ItemCategory);

	if (index == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("You don't have that item."));
		return false;
	}

	// Find Upgrades 
	FName upgradeName;

	switch (ItemToUpgrade.ItemCategory)
	{
	case EItemCategory::Weapon :
		upgradeName = FName(*FString::Printf(TEXT("Upgrade%d"), ItemToUpgrade.ItemLevel));
		break;
	default :
		upgradeName = FName(TEXT("HolyWater"));
	}

	FItemStruct upgrade = *GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>()->GetItemInfoDB()->FindRow<FItemStruct>(upgradeName, TEXT("GetItemRow"));

	int upgradeIndex = GetItemIndex(upgrade.ID, upgrade.ItemCategory);

	if (upgradeIndex == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("You don't have upgrade."));
		return false;
	}

	if (Upgrades[upgradeIndex].Quantity < MaterialCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("You need more MaterialCount."));
		return false;
	}

	DeleteItem(upgrade, MaterialCount);
	slots[index].Item.ItemLevel++;

	UE_LOG(LogTemp, Warning, TEXT("Upgrade Complete."));

	return true;
}

bool UInventoryComponent::DeleteItem(FItemStruct ItemToDelete, int Quantity)
{
	TArray<FInventorySlot>& slots = GetContents(ItemToDelete.ItemCategory);

	int index = GetItemIndex(ItemToDelete.ID, ItemToDelete.ItemCategory);

	if (index == -1)
		return false;

	slots[index].Quantity -= Quantity;

	if (slots[index].Quantity <= 0 && slots[index].Item.bDestroyable)
	{
		slots[index] = FInventorySlot();

		FInventorySlot tmp1, tmp2 = slots[index + 1];

		for (index; index < slots.Num(); index++)
		{
			if (slots[index].Item.ID == 1)
				break;

			tmp1 = slots[index];
			slots[index] = tmp2;
			tmp2 = tmp1;
		}
		
		UE_LOG(LogTemp, Warning, TEXT("destroy item and add new empty slot"));
	}

	UpdateSlots(slots);

	return true;
}

bool UInventoryComponent::UpdateSlots(TArray<FInventorySlot>& Slots)
{
	if (Slots.Num() <= ExpansionSize)
		return false;

	int emptySlotCnt = 0;

	for (int i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i].Item.ID == 1)
			emptySlotCnt++;
	}

	int iterCnt = emptySlotCnt / ExpansionSize;
	int indexToDelete = Slots.Num() - (iterCnt * ExpansionSize);

	for (int i = 0; i < iterCnt; i++)
	{
		Slots.RemoveAt(indexToDelete);
	}

	return true;
}

bool UInventoryComponent::AddNewSlot(TArray<FInventorySlot>& Slots)
{
	UE_LOG(LogTemp, Warning, TEXT("AddNewSlot"))
	Slots.AddDefaulted(ExpansionSize);

	return true;
}

bool UInventoryComponent::UseAstral(int Cost)
{
	if (Astral < Cost)
		return false;

	Astral -= Cost;

	return true;
}

bool UInventoryComponent::AddAstral(int Amount)
{
	if (Astral + Amount < INT_MAX)
	{
		Astral = INT_MAX;
		return false;
	}

	Astral += Amount;

	return true;
}

