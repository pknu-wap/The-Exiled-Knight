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
	Shard,	// defense or specific effect
	Hunting,	// monster drop item
	Upgrades,	// weapon & potion upgrade
	Rune,	// Special skill
};

UENUM(BlueprintType)
enum class EEquipCategory : uint8
{
	None,
	Weapon,
	Rune,
	FragmentOfGod,
	UsableItem,
	Magic
};