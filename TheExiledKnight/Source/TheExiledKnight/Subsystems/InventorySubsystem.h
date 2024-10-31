// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Structs/ItemStruct.h"
#include "InventorySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UInventorySubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	TObjectPtr<UDataTable> GetItemDB() { return ItemDB; };
	FItemStruct* GetItemRow(FName RowName);
	FItemStruct* GetItemInfo(uint8 ID);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> ItemDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TMap<uint8, FItemStruct> ItemDictionary;
};
