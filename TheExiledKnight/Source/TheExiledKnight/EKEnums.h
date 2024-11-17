// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	GreatSword,
	Spear,
	Staff
};

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	None,
	Weapon,
	Rune,			// defense or specific effect
	FragmentOfGod,	// Special skill
	UseableItem,		// Useable Item
	Magic,
	Upgrades,		// weapon & potion upgrade Items
	Hunting			// monster drop item
};