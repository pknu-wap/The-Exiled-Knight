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
}