// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_InvContentList.generated.h"

class UListView;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_InvContentList : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UListView* ContentList;
};