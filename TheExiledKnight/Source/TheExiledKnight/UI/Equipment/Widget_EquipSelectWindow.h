// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_EquipSelectWindow.generated.h"

class UTextBlock;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_EquipSelectWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UTextBlock* Text_Category;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UTextBlock* Text_SelectedItem;
};
