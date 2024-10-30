// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EKEnums.h"
#include "Widget_Inventory.generated.h"

class UButton;
class UScrollBox;
class UWidget_InvContentList;
class UWidget_Inventory_CategorySlot;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_Inventory : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateContents(EItemCategory Category);

public:
	UFUNCTION()
	void ShowBeforeCategory();

	UFUNCTION()
	void ShowNextCategory();

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_InvContentList* ContentList;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UScrollBox* ScrollBox_Category;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UButton* Button_BeforeCategory;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UButton* Button_NextCategory;

private:
	TArray<UWidget_Inventory_CategorySlot*> CategorySlots;
	int CurrentCategoryIdx;
};
