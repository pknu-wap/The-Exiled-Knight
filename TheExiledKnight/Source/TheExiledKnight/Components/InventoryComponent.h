// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/InventorySlotStruct.h"
#include "EKEnums.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAdd_Item_Delegate);

#define UPGRADE "Upgrade"
#define HEALTH_POTION_ID 2
#define MANA_POTION_ID 3
#define OLIVELEAF_ID 5
#define MAX_ITEM_LEVEL 10

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class THEEXILEDKNIGHT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	TArray<FInventorySlot>& GetContents(EItemCategory Category);

	const TArray<FInventorySlot> GetContents(EUpgradeItemType Category);
	const TArray<FInventorySlot>& GetConstContents(EItemCategory Category);

	int GetIndexToAdd(uint8 ID, EItemCategory Category);
	int GetItemIndex(uint8 ID, EItemCategory Category);
	int GetEmptySlotIndex(EItemCategory Category);

	UFUNCTION(BlueprintCallable)
	bool AddItem(FItemStruct ItemToAdd, int Quantity = 1);

	UFUNCTION(BlueprintCallable)
	bool UseItem(FItemStruct ItemToUse, int Quantity = 1);

	UFUNCTION(BlueprintCallable)
	bool UpgradeItem(FItemStruct ItemToUpgrade, FItemStruct Upgrade = FItemStruct(), int MaterialCount = 1);

	UFUNCTION(BlueprintCallable)
	bool DeleteItem(FItemStruct ItemToDelete, int Quantity = 0);

	UFUNCTION(BlueprintCallable)
	bool UpdateSlots(TArray<FInventorySlot>& Slots);

	UFUNCTION(BlueprintCallable)
	bool AddNewSlot(TArray<FInventorySlot>& Slots);

	UFUNCTION(BlueprintCallable)
	bool UseAstral(int Cost);

	UFUNCTION(BlueprintCallable)
	void AddAstral(int Amount);

	UFUNCTION(BlueprintCallable)
	bool RestorePotionQuantity();

	UFUNCTION(BlueprintCallable)
	bool DividePotion(int HealthPotionQuantity, int ManaPotionQuantity);

	UPROPERTY(BlueprintAssignable)
	FAdd_Item_Delegate AddItemDelegate;


private:
	void InitializeInventory();

private:
	TArray<FInventorySlot> None;

	TArray<FInventorySlot> Weapon;

	TArray<FInventorySlot> Rune;

	TArray<FInventorySlot> FragmentOfGod;

	TArray<FInventorySlot> UseableItem;

	TArray<FInventorySlot> Magic;

	TArray<FInventorySlot> Upgrades;

	TArray<FInventorySlot> Hunting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	int ExpansionSize = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	int Astral = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	int TotalPotionQuantity = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	int MaxHealthPotionQuantity = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	int MaxManaPotionQuantity = 1;
};
