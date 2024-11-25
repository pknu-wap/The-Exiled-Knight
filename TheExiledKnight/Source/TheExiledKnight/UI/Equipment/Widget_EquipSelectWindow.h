// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EKEnums.h"
#include "Structs/InventorySlotStruct.h"
#include "Player/Data/EKPlayerMagic.h"
#include "Widget_EquipSelectWindow.generated.h"

class UTextBlock;
class UImage;
class UOverlay;
class UWidgetSwitcher;
class UWidget_EquipSelect_ContentList;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_EquipSelectWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	void UpdateContents(EItemCategory Category);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDescription_Item(const FInventorySlot& SlotData);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDescription_Magic(const FEKPlayerMagic& SlotData);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDescription_Weapon(const FInventorySlot& SlotData);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDescription_Rune(const FInventorySlot& SlotData);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateStatusInfo();

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UTextBlock* Text_Category;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UTextBlock* Text_SelectedItem;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UImage* Image_Item;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_EquipSelect_ContentList* ContentList;

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UOverlay* Overlay_Item;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UOverlay* Overlay_Weapon;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UOverlay* Overlay_Rune;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UOverlay* Overlay_Fragment;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UOverlay* Overlay_Magic;
};
