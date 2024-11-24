// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Structs/ItemStruct.h"
#include "Item/EKItem_Base.h"
#include "InventorySubsystem.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UInventorySubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	TObjectPtr<UDataTable> GetItemInfoDB() { return ItemInfoDB; };
	TObjectPtr<UDataTable> GetItemClassDB() { return ItemClassDB; };
	const FItemStruct* GetItemInfo(uint8 ID);

	AEKItem_Base* CreateItemInstance(uint8 ID);

	FLevelRate* GetLevelRateInfo(int level);

	FWeaponStruct* GetWeaponInfo(uint8 ID);
	FRune* GetRuneInfo(uint8 ID);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> ItemInfoDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> ItemClassDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> LevelRateDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TMap<uint8, FItemStruct> ItemDictionary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TMap<uint8, TSubclassOf<AEKItem_Base>> ItemInstanceDictionary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> WeaponDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TMap<uint8, FWeaponStruct> WeaponDictionary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> RuneDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TMap<uint8, FRune> RuneDictionary;
};
