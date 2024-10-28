// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameMenu/Widget_GameMenu_Button.h"
#include "Components/Button.h"
#include "UI/UISubsystem.h"
#include "EKGameplayTags.h"

void UWidget_GameMenu_Button::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Menu->OnClicked.AddUniqueDynamic(this, &UWidget_GameMenu_Button::MenuButtonClicked);
}

void UWidget_GameMenu_Button::MenuButtonClicked()
{
	UUISubsystem* UIManager = GetGameInstance()->GetSubsystem<UUISubsystem>();
	if (!UIManager) return;

	switch (MenuCategory)
	{
	case EGameMenuCategory::Inventory:
	{
		UIManager->SetWidgetVisibility(FEKGameplayTags::Get().UI_Widget_GameMenu_GameMenu, ESlateVisibility::Collapsed);
		UIManager->SetWidgetVisibility(FEKGameplayTags::Get().UI_Widget_GameMenu_Inventory, ESlateVisibility::Visible);
		break;
	}
	case EGameMenuCategory::Equipment:
	{
		UIManager->SetWidgetVisibility(FEKGameplayTags::Get().UI_Widget_GameMenu_GameMenu, ESlateVisibility::Collapsed);
		UIManager->SetWidgetVisibility(FEKGameplayTags::Get().UI_Widget_GameMenu_Equipment, ESlateVisibility::Visible);
		break;
	}
	case EGameMenuCategory::Option:
	{
		break;
	}
	case EGameMenuCategory::Quit:
	{

		break;
	}
	default:
		break;
	}
}
