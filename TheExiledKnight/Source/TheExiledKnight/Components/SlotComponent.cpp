// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SlotComponent.h"
#include "UI/UISubsystem.h"
#include "EKGameplayTags.h"
#include "UI/Equipment/Widget_Equipment.h"
#include "Subsystems/InventorySubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Player/EKPlayer/EKPlayer.h"

// Sets default values for this component's properties
USlotComponent::USlotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USlotComponent::BeginPlay()
{
	Super::BeginPlay();

	for(int i = 0; i < 2; i++)
		WeaponSlots.Add(FItemStruct());
	for (int i = 0; i < 4; i++)
		RuneSlots.Add(FItemStruct());
	for (int i = 0; i < 4; i++)
		UsableSlots.Add(FItemStruct());
	for (int i = 0; i < 6; i++)
		MagicSlots.Add(FMagicStruct());
}


// Called every frame
void USlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USlotComponent::EquipWeapon(const FItemStruct& InItemData)
{
	UWidget_Equipment* equipWidget = GetEquipmentWidget();
	if (!equipWidget) return;

	UInventorySubsystem* inventorySystem =
		GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	if (!inventorySystem) return;

	FWeaponStruct* weaponInfo = inventorySystem->GetWeaponInfo(InItemData.ID);
	if (!weaponInfo) return;

	AEKPlayer* player = Cast<AEKPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!player) return;

	int slotIdx = equipWidget->GetEquipSelectSlotIdx();
	if (WeaponSlots.IsValidIndex(slotIdx))
	{
		WeaponSlots[slotIdx] = InItemData;
		player->EquipWeapon(*weaponInfo);
		Delegate_SlotUpdated.Broadcast(EEquipCategory::Weapon, slotIdx);
	}
}

void USlotComponent::EquipRune(const FItemStruct& InItemData)
{
	UWidget_Equipment* equipWidget = GetEquipmentWidget();
	if (!equipWidget) return;

	int slotIdx = equipWidget->GetEquipSelectSlotIdx();
	if (RuneSlots.IsValidIndex(slotIdx))
	{
		RuneSlots[slotIdx] = InItemData;
		Delegate_SlotUpdated.Broadcast(EEquipCategory::Rune, slotIdx);
	}
}

void USlotComponent::EquipUsableItem(const FItemStruct& InItemData)
{
	UWidget_Equipment* equipWidget = GetEquipmentWidget();
	if (!equipWidget) return;

	int slotIdx = equipWidget->GetEquipSelectSlotIdx();
	if (UsableSlots.IsValidIndex(slotIdx))
	{
		UsableSlots[slotIdx] = InItemData;
		Delegate_SlotUpdated.Broadcast(EEquipCategory::UsableItem, slotIdx);
	}
}

void USlotComponent::EquipMagic(const FMagicStruct& InMagicData)
{
}

UWidget_Equipment* USlotComponent::GetEquipmentWidget()
{
	UUISubsystem* UISystem = GetWorld()->GetGameInstance()->GetSubsystem<UUISubsystem>();
	if (!UISystem) return nullptr;

	UUserWidget* widget = UISystem->GetWidget(FEKGameplayTags::Get().UI_Widget_GameMenu_Equipment);
	if (!widget) return nullptr;

	UWidget_Equipment* equipWidget = Cast<UWidget_Equipment>(widget);
	return equipWidget;
}

