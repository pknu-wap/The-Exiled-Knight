// Fill out your copyright notice in the Description page of Project Settings.


#include "EK_EnemyStatusComponent.h"

// Sets default values for this component's properties
UEK_EnemyStatusComponent::UEK_EnemyStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PoiseLevel = 1;
	MaxHealth = 100;
	CurrentHealth = MaxHealth;
	MaxPosie = 10;
	CurrentPosie = MaxPosie;
	bIsDead = false;
	
}


void UEK_EnemyStatusComponent::TakeDamage(float amount)
{
	if (GetIsDead())return;
	CurrentHealth -= amount;
	if (CurrentHealth <= 0)
	{
		bIsDead = true;
		
	}

}

uint8 UEK_EnemyStatusComponent::GetPosieLevel()
{
	return PoiseLevel;
}

float UEK_EnemyStatusComponent::GetMaxHealth()
{
	return MaxHealth;
}

float UEK_EnemyStatusComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float UEK_EnemyStatusComponent::GetMaxPoise()
{
	return MaxPosie;
}

float UEK_EnemyStatusComponent::GetCurrentPoise()
{
	return CurrentPosie;
}

bool UEK_EnemyStatusComponent::GetIsDead()
{
	return bIsDead;
}







