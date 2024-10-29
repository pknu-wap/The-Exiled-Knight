// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment/Widget_EquipSelect_ContentSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UWidget_EquipSelect_ContentSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

FEventReply UWidget_EquipSelect_ContentSlot::RedirectMouseDownToWidget(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
	{
		// Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	}

	return Reply;
}
