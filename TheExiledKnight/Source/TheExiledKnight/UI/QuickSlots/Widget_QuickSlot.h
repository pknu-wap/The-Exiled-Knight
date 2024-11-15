// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EKEnums.h"
#include "Widget_QuickSlot.generated.h"

class UButton;
class UImage;
class UTextBlock;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_QuickSlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void SlotUpdated(EEquipCategory inCategory, int inSlotIdx);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipCategory SlotCategory;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UButton* Button_Slot;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UImage* Image_Item;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UTextBlock* Text_Quantity;

public:
	int GetActiveSlotIdx() { return ActiveSlotIdx; }

private:
	int ActiveSlotIdx = 0;
};
