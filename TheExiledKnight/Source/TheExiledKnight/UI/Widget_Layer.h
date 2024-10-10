// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Layer.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UWidget_Layer : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	UUserWidget* PushContent(const TSoftClassPtr<UUserWidget>& WidgetClass);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PopContent();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CollapseTop();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowTop();
};
