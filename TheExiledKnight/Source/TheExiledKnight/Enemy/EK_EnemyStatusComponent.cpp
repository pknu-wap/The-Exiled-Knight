// Fill out your copyright notice in the Description page of Project Settings.


#include "EK_EnemyStatusComponent.h"

// Sets default values for this component's properties
UEK_EnemyStatusComponent::UEK_EnemyStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetPoiseLevel(1);
	SetMaxHealth(100);
	SetCurrentHealth(GetMaxHealth());
	SetMaxPoise(10);
	SetCurrentPoise(GetMaxPoise());
	SetIsDead(false);
	
}


void UEK_EnemyStatusComponent::TakeDamage(float amount)
{
	SetCurrentHealth(FMath::Clamp<float>(GetCurrentHealth() - amount, 0.0f, GetMaxHealth()));
	if (CurrentHealth <= 0.0f)
	{
		OnHPIsZero.Broadcast();
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

void UEK_EnemyStatusComponent::SetPoiseLevel(uint8 amount)
{
	PoiseLevel = amount;
}

void UEK_EnemyStatusComponent::SetMaxHealth(float amount)
{
	MaxHealth = amount;
}

void UEK_EnemyStatusComponent::SetCurrentHealth(float amount)
{
	CurrentHealth = amount;
}

void UEK_EnemyStatusComponent::SetMaxPoise(float amount)
{
	MaxPosie = amount;
}

void UEK_EnemyStatusComponent::SetCurrentPoise(float amount)
{
	CurrentPosie = amount;
}

void UEK_EnemyStatusComponent::SetIsDead(bool isDead)
{
	bIsDead = isDead;
}







