// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EKPotion_Base.h"

void AEKPotion_Base::UseItem()
{
	Super::UseItem();

	// Heal Health, Mana, etc...
	UE_LOG(LogTemp, Warning, TEXT("Use Potion Base"));
}
