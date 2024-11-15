// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/Widget_InvContentSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/InventoryComponent.h"
#include "Kismet/KismetTextLibrary.h"

void UWidget_InvContentSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_InvContentSlot::UpdateSlot(int slotIdx, const FInventorySlot& inData)
{
	SlotIdx = slotIdx;
	if (inData.Amount > 0)
	{
		Image_Item->SetBrushFromTexture(inData.Item.Icon);
		Text_Quantity->SetText(UKismetTextLibrary::Conv_IntToText(inData.Amount));
	}
}

FEventReply UWidget_InvContentSlot::RedirectMouseDownToWidget(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
	{
		// Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	}

	return Reply;
}
