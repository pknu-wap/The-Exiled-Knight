// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EKEnums.h"
#include "Widget_EU_CategorySlot.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UWidget_EU_CategorySlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	FEventReply RedirectMouseDownToWidget(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Hover();

	UFUNCTION(BlueprintImplementableEvent)
	void UnHover();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EUpgradeItemType Category = EUpgradeItemType::Sword;
};
