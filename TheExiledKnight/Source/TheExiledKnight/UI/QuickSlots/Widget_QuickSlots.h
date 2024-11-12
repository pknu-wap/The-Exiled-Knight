// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_QuickSlots.generated.h"

class UWidget_QuickSlot;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_QuickSlots : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_QuickSlot* QuickSlot_Weapon;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_QuickSlot* QuickSlot_Fragment;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_QuickSlot* QuickSlot_Magic;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UWidget_QuickSlot* QuickSlot_UsableItem;
};
