// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EKEnums.h"
#include "Widget_Inventory_CategorySlot.generated.h"

class UButton;
class UImage;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_Inventory_CategorySlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	FEventReply RedirectMouseDownToWidget(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Hover();

	UFUNCTION(BlueprintImplementableEvent)
	void UnHover();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemCategory Category;

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UButton* Button_Category;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UImage* Image_Category;
};
