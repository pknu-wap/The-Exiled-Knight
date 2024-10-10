// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FEKGameplayTags
{

public:
	static const FEKGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeGameplayTags();

	// UI
	FGameplayTag UI_Layer_Game;			// Player Status, Weapon Slots . . .
	FGameplayTag UI_Layer_GameMenu;		// Inventory, Quest . . .
	FGameplayTag UI_Layer_Menu;			// Option . . .

	FGameplayTag UI_Widget_Inventory;	// Inventory
	FGameplayTag UI_Widget_Equipment;	// Equipment

private:
	static FEKGameplayTags GameplayTags;
};