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
	const TArray<FInventorySlot>& GetContents(EItemCategory Category);
	const TArray<FInventorySlot>& GetContents(EEquipCategory Category);

	int GetIndexToAdd(uint8 ID);
	int GetDupSlotIndex(uint8 ID, int MaxStack);
	int GetEmptySlotIndex();

	UFUNCTION(BlueprintCallable)
	TArray<FInventorySlot>& GetInventory() { return Inventory; }

	UFUNCTION(BlueprintCallable)
	bool AddItem(FItemStruct ItemToAdd);


private:
	void InitializeInventory();




private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> ItemDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FInventorySlot> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	int Inventory_Size = 5;
};
