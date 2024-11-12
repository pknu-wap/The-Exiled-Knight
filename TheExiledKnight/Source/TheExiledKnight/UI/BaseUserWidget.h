// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void OnVisibilityToggled(ESlateVisibility InVisibility) {};

	UFUNCTION(BlueprintImplementableEvent)
	void K2_OnVisibilityToggled(ESlateVisibility InVisibility);
};
