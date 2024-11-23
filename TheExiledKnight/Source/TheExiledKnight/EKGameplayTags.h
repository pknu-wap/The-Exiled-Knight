// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FEKGameplayTags
{

public:
	static const FEKGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeGameplayTags();

	////////// UI /////////

	// Layer
	FGameplayTag UI_Layer_Game;			// Player Status, Weapon Slots . . .
	FGameplayTag UI_Layer_GameMenu;		// Inventory, Quest . . .
	FGameplayTag UI_Layer_Menu;			// Option . . .

	// Widget
	FGameplayTag UI_Widget_GameMenu_GameMenu;			// GameMenu
	FGameplayTag UI_Widget_GameMenu_Inventory;			// Inventory
	FGameplayTag UI_Widget_GameMenu_Equipment;			// Equipment
	FGameplayTag UI_Widget_GameMenu_EquipSelect;		// Equip Select
	FGameplayTag UI_Widget_GameMenu_UpgradeStatus;		// Upgrade Status
	FGameplayTag UI_Widget_GameMenu_UpgradeEquipment;	// Upgrade Equipment
	FGameplayTag UI_Widget_GameMenu_Setting;			// Setting

	FGameplayTag UI_Widget_GameMenu_Santuary;			// Santuary
	FGameplayTag UI_Widget_GameMenu_Map;				// Map Change
	FGameplayTag UI_Widget_GameMenu_Potion;				// Potion Distribute

	FGameplayTag UI_Widget_Game_Status;					// Status
	FGameplayTag UI_Widget_Game_QuickSlots;				// QuickSlots
	FGameplayTag UI_Widget_Game_BossBattle;				// Boss Battle

	FGameplayTag UI_Widget_Menu_MainMenu;				// Setting
	FGameplayTag UI_Widget_Menu_Setting;				// Setting


private:
	static FEKGameplayTags GameplayTags;
};