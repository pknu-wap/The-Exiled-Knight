// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/InventorySlotStruct.h"
#include "EKEnums.h"
#include "InventoryComponent.generated.h"

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
	const TArray<FInventorySlot>& GetConstInventory(EItemCategory Category);
	const TArray<FInventorySlot>& GetEquipContents(EEquipCategory Category);

	UFUNCTION(BlueprintCallable)
	TArray<FInventorySlot>& GetInventory(EItemCategory Category);

	int GetIndexToAdd(uint8 ID, EItemCategory Category);
	int GetDupSlotIndex(uint8 ID, EItemCategory Category);
	int GetEmptySlotIndex(EItemCategory Category);

	UFUNCTION(BlueprintCallable)
	bool AddItem(FItemStruct ItemToAdd, int Quantity = 1);

	UFUNCTION(BlueprintCallable)
	bool UseItem(FItemStruct ItemToUse, int Quantity = 1);

	UFUNCTION(BlueprintCallable)
	bool DeleteItem(FItemStruct ItemToDelete, int Quantity = 0);

	UFUNCTION(BlueprintCallable)
	bool DeleteSlots(TArray<FInventorySlot>& Slots);

	UFUNCTION(BlueprintCallable)
	bool AddNewSlot(TArray<FInventorySlot>& Slots);


private:
	void InitializeInventory();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> Fragment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> Hunting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> Upgrades;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> Rune;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	int ExpansionSize = 5;
};
