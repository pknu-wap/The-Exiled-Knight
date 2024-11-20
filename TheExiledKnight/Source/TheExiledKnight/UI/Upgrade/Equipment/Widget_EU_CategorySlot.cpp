// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Upgrade/Equipment/Widget_EU_CategorySlot.h"
#include "UI/Upgrade/Equipment/Widget_UpgradeEquipment.h"
#include "UI/UISubsystem.h"
#include "EKGameplayTags.h"

FEventReply UWidget_EU_CategorySlot::RedirectMouseDownToWidget(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
	{
		UUISubsystem* UISystem = GetGameInstance()->GetSubsystem<UUISubsystem>();
		if (!UISystem) return Reply;

		UUserWidget* widget =
			UISystem->GetWidget(FEKGameplayTags::Get().UI_Widget_GameMenu_UpgradeEquipment);
		if (!widget) return Reply;

		UWidget_UpgradeEquipment* EUWidget = Cast<UWidget_UpgradeEquipment>(widget);
		if (!EUWidget) return Reply;

		EUWidget->UpdateContents(Category);
	}

	return Reply;
}
