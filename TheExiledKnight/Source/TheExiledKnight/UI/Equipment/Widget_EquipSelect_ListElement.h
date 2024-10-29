// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget_EquipSelect_ListElement.generated.h"

class UWidget_EquipSelect_ContentSlot;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_EquipSelect_ListElement : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_EquipSelect_ContentSlot* Slot_01;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_EquipSelect_ContentSlot* Slot_02;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_EquipSelect_ContentSlot* Slot_03;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_EquipSelect_ContentSlot* Slot_04;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_EquipSelect_ContentSlot* Slot_05;
};
