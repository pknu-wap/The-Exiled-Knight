// Fill out your copyright notice in the Description page of Project Settings.


#include "EK_EnemyStatusComponent.h"
#include "EKEnemyData.h"

// Sets default values for this component's properties
#pragma region LifeCycle
UEK_EnemyStatusComponent::UEK_EnemyStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}
void UEK_EnemyStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	InitSetting();
}
#pragma endregion


#pragma region InitialSetting

void UEK_EnemyStatusComponent::InitSetting()
{
	if (EnemyDataTable)
	{
		static const FString ContextString(TEXT("Enemy Data Context"));
		FEnemyData* FoundData = EnemyDataTable->FindRow<FEnemyData>(EnemyID, ContextString);
		if (FoundData)
		{
			SetHealth(FoundData->Health);
			SetAttackDamage(FoundData->Damage);
			SetCurrentSpeed(FoundData->CurrentSpeed);
			SetMaxSpeed(FoundData->MaxSpeed);
			SetPoise(FoundData->PoiseAmount);
			SetSightRange(FoundData->SightRange);
			SetHearingRange(FoundData->HearingRange);
			SetIsDead(false);
			Astral = FoundData->Astral;
			DropItem = FoundData->DropItem;
			bIsBoss = FoundData->bIsBoss;
		}
	}
}
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
void UEK_EnemyStatusComponent::SetCurrentSpeed(float amount)
{
	CurrentSpeed = amount;
}
void UEK_EnemyStatusComponent::SetMaxSpeed(float amount)
{
	MaxSpeed = amount;
}
void UEK_EnemyStatusComponent::SetSightRange(float amount)
{
	SightRadius = amount;
}
void UEK_EnemyStatusComponent::SetHearingRange(float amount)
{
	HearingRange = amount;
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

float UEK_EnemyStatusComponent::GetMaxSpeed()
{
	return  MaxSpeed;
}

float UEK_EnemyStatusComponent::GetCurrentSpeed()
{
	return CurrentSpeed;
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












