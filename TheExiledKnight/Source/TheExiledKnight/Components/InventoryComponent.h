// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/InventorySlotStruct.h"
#include "EKEnums.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FAdd_Item_Delegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

	int GetIndexToAdd(uint8 ID);
	int GetDupSlotIndex(uint8 ID, int MaxStack);
	int GetEmptySlotIndex();

	int GetIndexToAdd(uint8 ID, EItemCategory Category);
	int GetDupSlotIndex(uint8 ID, EItemCategory Category);
	int GetEmptySlotIndex(EItemCategory Category);

	UFUNCTION(BlueprintCallable)
	bool AddItem(FItemStruct ItemToAdd, int Quantity = 1);

	UFUNCTION(BlueprintCallable)
	bool UseItem(FItemStruct ItemToUse, int Quantity = 1);

	UFUNCTION(BlueprintCallable)
	bool UpgradeItem(FItemStruct ItemToUpgrade);

	UFUNCTION(BlueprintCallable)
	bool DeleteItem(FItemStruct ItemToDelete, int Quantity = 0);

	UFUNCTION(BlueprintCallable)
	bool UpdateSlots(TArray<FInventorySlot>& Slots);

	UFUNCTION(BlueprintCallable)
	bool AddNewSlot(TArray<FInventorySlot>& Slots);

	FAdd_Item_Delegate AddItemDelegate;


private:
	void InitializeInventory();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> Rune;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> FragmentOfGod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> UseableItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> Magic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> Upgrades;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> Hunting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	int ExpansionSize = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	int64 Astral = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	int TotalPotionQuantity = 4;
};
