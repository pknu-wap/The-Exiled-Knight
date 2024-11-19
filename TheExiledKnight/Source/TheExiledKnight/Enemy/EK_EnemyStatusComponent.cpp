// Fill out your copyright notice in the Description page of Project Settings.


#include "EK_EnemyStatusComponent.h"

// Sets default values for this component's properties
UEK_EnemyStatusComponent::UEK_EnemyStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetHealth(1000);
	SetPoise(100);
	SetAttackDamage(1);
	SetIsDead(false);
}
#pragma region InitialSetting

void UEK_EnemyStatusComponent::SetHealth(float amount)
{
	MaxHealth = amount;
	CurrentHealth = MaxHealth;
}

void UEK_EnemyStatusComponent::SetAttackDamage(float amount)
{
	AttackDamage = amount;
}

void UEK_EnemyStatusComponent::SetPoise(float amount)
{
	MaxPoise = amount;
	CurrentPoise = MaxPoise;
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

float UEK_EnemyStatusComponent::GetSightRange()
{
	return SightRadius;
}

float UEK_EnemyStatusComponent::GetHearingRange()
{
	return HearingRange;
}

bool UEK_EnemyStatusComponent::GetIsDead()
{
	return bIsDead;
}
#pragma endregion

#pragma region ChangeStat
void UEK_EnemyStatusComponent::DamageCurrentPoise(float amount)
{
	CurrentPoise -= amount;
}

void UEK_EnemyStatusComponent::DamageCurrentHealth(float amount)
{
	CurrentHealth -= amount;
}

#pragma endregion
#pragma region ResetPoise
void UEK_EnemyStatusComponent::ResetCurrentPoise()
{
	CurrentPoise = MaxPoise;
}
#pragma endregion












