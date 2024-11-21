// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/InventorySlotStruct.h"
#include "EKEnums.h"
#include "Widget_UpgradeEquipment.generated.h"

class UButton;
class UScrollBox;
class UWidget_InvContentList;
class UWidget_EU_CategorySlot;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_UpgradeEquipment : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateContents(EUpgradeItemType WidgetType);

	UFUNCTION(BlueprintCallable)
	void LevelUp_Equipment(const FItemStruct& InItem);

public:
	UFUNCTION()
	void ShowBeforeCategory();

	UFUNCTION()
	void ShowNextCategory();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDescription(const FInventorySlot& SlotData);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowConfirmWidget(const FInventorySlot& SlotData);

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_InvContentList* ContentList;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UScrollBox* ScrollBox_Category;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UButton* Button_BeforeCategory;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UButton* Button_NextCategory;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EUpgradeItemType CurrentType;

private:
	TArray<UWidget_EU_CategorySlot*> CategorySlots;
	int CurrentCategoryIdx;
};
