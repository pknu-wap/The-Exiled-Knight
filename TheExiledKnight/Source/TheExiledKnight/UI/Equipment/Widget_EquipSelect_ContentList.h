// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_EquipSelect_ContentList.generated.h"

class UListView;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_EquipSelect_ContentList : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UListView* ContentList;
};
