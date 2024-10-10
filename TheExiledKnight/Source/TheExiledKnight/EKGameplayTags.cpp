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

	GameplayTags.UI_Widget_Inventory = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("UI.Widget.Inventory"),
		FString("Inventory")
	);

	GameplayTags.UI_Widget_Equipment = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("UI.Widget.Equipment"),
		FString("Equipment")
	);
	
}