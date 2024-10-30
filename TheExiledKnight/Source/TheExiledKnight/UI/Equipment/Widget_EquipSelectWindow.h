// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EKEnums.h"
#include "Widget_EquipSelectWindow.generated.h"

class UTextBlock;
class UImage;
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
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UTextBlock* Text_Category;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UTextBlock* Text_SelectedItem;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UImage* Image_Item;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_EquipSelect_ContentList* ContentList;
};
