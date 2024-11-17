// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ItemStruct.h"
#include "EKEnums.h"
#include "SlotComponent.generated.h"

USTRUCT(BlueprintType)
struct FMagicStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MagicID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MagicName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString MagicDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FSlotUpdated, EItemCategory, int)

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
	void EquipMagic(const FMagicStruct& InMagicData);

private:
	class UWidget_Equipment* GetEquipmentWidget();

public:
	// Weapons
	TArray<FItemStruct> WeaponSlots;

	// Rune
	TArray<FItemStruct> RuneSlots;

	// Usable Items
	TArray<FItemStruct> UsableSlots;

	// Magics
	TArray<FMagicStruct> MagicSlots;

	// Special Skill
	
public:
	FSlotUpdated Delegate_SlotUpdated;
};
