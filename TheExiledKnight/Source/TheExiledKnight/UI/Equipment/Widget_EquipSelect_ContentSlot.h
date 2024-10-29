// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_EquipSelect_ContentSlot.generated.h"

class UButton;
class UImage;
class UTextBlock;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_EquipSelect_ContentSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable)
	FEventReply RedirectMouseDownToWidget(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UButton* Button_Slot;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UImage* Image_Item;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UTextBlock* Text_Quantity;
};
