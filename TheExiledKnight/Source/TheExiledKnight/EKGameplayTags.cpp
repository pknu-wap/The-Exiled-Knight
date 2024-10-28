// Fill out your copyright notice in the Description page of Project Settings.


#include "EKGameplayTags.h"
#include "GameplayTagsManager.h"

FEKGameplayTags FEKGameplayTags::GameplayTags;

void FEKGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.UI_Layer_Game = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("UI.Layer.Game"),
		FString("Player Status, Weapon Slots . . .")
	);

	GameplayTags.UI_Layer_GameMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("UI.Layer.GameMenu"),
		FString("Inventory, Quest . . .")
	);

	GameplayTags.UI_Layer_Menu = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("UI.Layer.Menu"),
		FString("Option . . .")
	);

	GameplayTags.UI_Widget_GameMenu_GameMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("UI.Widget.GameMenu.GameMenu"),
		FString("GameMenu")
	);

	GameplayTags.UI_Widget_GameMenu_Inventory = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("UI.Widget.GameMenu.Inventory"),
		FString("Inventory")
	);

	GameplayTags.UI_Widget_GameMenu_Equipment = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("UI.Widget.GameMenu.Equipment"),
		FString("Equipment")
	);
	
}