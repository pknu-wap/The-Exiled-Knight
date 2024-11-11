// Fill out your copyright notice in the Description page of Project Settings.


#include "EK_EnemyStatusComponent.h"

// Sets default values for this component's properties
UEK_EnemyStatusComponent::UEK_EnemyStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetMaxHealth(100);
	ChangeCurrentHealth(GetMaxHealth());
	SetMaxPoise(10);
	SetAttackDamage(10);
	ChangeCurrentPoise(GetMaxPoise()); 
	SetIsDead(false);
}
#pragma region InitialSetting

void UEK_EnemyStatusComponent::SetMaxHealth(float amount)
{
	MaxHealth = amount;
}

void UEK_EnemyStatusComponent::SetAttackDamage(float amount)
{
	AttackDamage = amount;
}

void UEK_EnemyStatusComponent::SetMaxPoise(float amount)
{
	MaxPoise = amount;
}
void UEK_EnemyStatusComponent::SetIsDead(bool isDead)
{
	bIsDead = isDead;
}
#pragma endregion


#pragma region GetStat

float UEK_EnemyStatusComponent::GetMaxHealth()
{
	return MaxHealth;
}
float UEK_EnemyStatusComponent::GetMaxPoise()
{
	return MaxPoise;
}
float UEK_EnemyStatusComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float UEK_EnemyStatusComponent::GetCurrentPoise()
{
	return CurrentPoise;
}

float UEK_EnemyStatusComponent::GetAttackDamage()
{
	return AttackDamage;
}

bool UEK_EnemyStatusComponent::GetIsDead()
{
	return bIsDead;
}
#pragma endregion

#pragma region ChangeStat
void UEK_EnemyStatusComponent::ChangeCurrentPoise(float amount)
{
	CurrentPoise -= amount;
}

void UEK_EnemyStatusComponent::ChangeCurrentHealth(float amount)
{
	CurrentHealth -= amount;
}

#pragma endregion










