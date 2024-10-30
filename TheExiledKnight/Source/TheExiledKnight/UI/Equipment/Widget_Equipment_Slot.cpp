// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment/Widget_Equipment_Slot.h"
#include "UI/Equipment/Widget_Equipment.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "UI/UISubsystem.h"
#include "EKGameplayTags.h"

FEventReply UWidget_Equipment_Slot::RedirectMouseDownToWidget(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
	{
		UUISubsystem* UISystem = GetGameInstance()->GetSubsystem<UUISubsystem>();
		if (!UISystem) return Reply;

		UUserWidget* widget =
			UISystem->GetWidget(FEKGameplayTags::Get().UI_Widget_GameMenu_Equipment);
		if (!widget) return Reply;

		UWidget_Equipment* EquipmentWidget = Cast<UWidget_Equipment>(widget);
		if (!EquipmentWidget) return Reply;

		EquipmentWidget->ShowEquipSelect(Category);
	} 

	return Reply;
}
