// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ItemStruct.h"
#include "EKEnums.h"
#include "Player/Data/EKPlayerMagic.h"
#include "SlotComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSlotUpdated, EItemCategory, InCategory, int, InSlotIdx);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FQuickSlotUpdated, EItemCategory, InCategory, int, InSlotIdx);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEEXILEDKNIGHT_API USlotComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlotComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void EquipWeapon(const FItemStruct& InItemData);
	void EquipRune(const FItemStruct& InItemData);
	void EquipUseableItem(const FItemStruct& InItemData);
	void EquipMagic(const FEKPlayerMagic& InMagicData);

public:
	void UpdateActiveSlot(EInputType InInputType);

private:
	class UWidget_Equipment* GetEquipmentWidget();

public:
	// Weapons
	TArray<FItemStruct> WeaponSlots;
	int ActiveWeaponSlot = 0;
	int MaxWeaponSlot = 2;

	// Rune
	TArray<FItemStruct> RuneSlots;
	int MaxRuneSlot = 4;

	// Usable Items
	TArray<FItemStruct> UseableSlots;
	int ActiveUseableSlot = 0;
	int MaxUseableSlot = 4;

	// Magics
	TArray<FEKPlayerMagic> MagicSlots;
	int ActiveMagicSlot = 0;
	int MaxMagicSlot = 6;

	// Special Skill
	int ActiveFragmentSlot = 0;
	int MaxFragmentSlot = 6;
	
public:
	UPROPERTY(BlueprintAssignable)
	FSlotUpdated Delegate_SlotUpdated;

	UPROPERTY(BlueprintAssignable)
	FQuickSlotUpdated Delegate_QuickSlotUpdated;
};
