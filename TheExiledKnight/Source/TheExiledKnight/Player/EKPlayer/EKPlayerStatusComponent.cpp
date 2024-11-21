// Made by Somalia Pirate

#include "EKPlayerStatusComponent.h"
#include "EKPlayer.h"
#include "EKPlayerController.h"
#include "../Weapon/EKPlayerWeapon.h"
#include "../EKPlayerGameplayTags.h"

UEKPlayerStatusComponent::UEKPlayerStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Edit Basic Status Value Here
	MaxHp = 1000;
	Hp = 1000;
	MaxMp = 1000;
	Mp = 1000;
	MaxStamina = 1000;
	Stamina = 1000;
	DefaultDamage = 10.f;
	FinalDamage = DefaultDamage;
	
	// Edit Basic Status Value Here
	Level = 1;
	Vitality = 0;
	Mental = 0;
	Endurance = 0;
	Strength = 0;
	Ability = 0;
	Intelligence = 0;
}


void UEKPlayerStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	EKPlayer = Cast<AEKPlayer>(GetOwner());

	if (EKPlayer)
	{
		EKPlayerController = Cast<AEKPlayerController>(EKPlayer->GetController());
	}
}


void UEKPlayerStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Stamina Recovery
	if (bCanStaminaRecovery)
	{
		SetStamina(4);
	}
}

#pragma region Set Basic Status

void UEKPlayerStatusComponent::SetMaxHp(int32 SetData)
{
	MaxHp = FMath::Clamp(MaxHp + SetData + (Vitality * 50), 0, PlayerMaxHp);
	SetHp(SetData);
}

void UEKPlayerStatusComponent::SetHp(int32 SetData)
{
	Hp = FMath::Clamp(Hp + SetData, 0, MaxHp);
	Delegate_HPUpdated.Broadcast(MaxHp, Hp);
}

void UEKPlayerStatusComponent::SetMaxMp(int32 SetData)
{
	MaxMp = FMath::Clamp(MaxMp + SetData + (Mental * 50), 0, PlayerMaxMp);
	SetMp(SetData);
}

void UEKPlayerStatusComponent::SetMp(int32 SetData)
{
	Mp = FMath::Clamp(Mp + SetData, 0, MaxMp);
	Delegate_MPUpdated.Broadcast(MaxMp, Mp);
}

void UEKPlayerStatusComponent::SetMaxStamina(int32 SetData)
{
	MaxStamina = FMath::Clamp(MaxStamina + SetData + (Endurance * 50), 0, PlayerMaxStamina);
	SetStamina(SetData);
}

void UEKPlayerStatusComponent::SetStamina(int32 SetData)
{
	Stamina = FMath::Clamp(Stamina + SetData, 0, MaxStamina);
	Delegate_StaminaUpdated.Broadcast(MaxStamina, Stamina);
}

#pragma endregion

#pragma region Damage

void UEKPlayerStatusComponent::SetPlayerDefaultDamage()
{

}

void UEKPlayerStatusComponent::SetPlayerFinalDamage()
{
	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_GreatSword))
	{
		FinalDamage = DefaultDamage + ((Strength * 10) * 1.5) + ((Ability * 10) * 0.8) + EKPlayer->GetCurrentWeapon()->WeaponAdditionalDamage;
	}
	else if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Spear))
	{
		FinalDamage = DefaultDamage + ((Ability * 10) * 1.5) + ((Strength * 10) * 0.8) + EKPlayer->GetCurrentWeapon()->WeaponAdditionalDamage;
	}
	else if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Staff))
	{
		FinalDamage = DefaultDamage + ((Intelligence * 10) * 1.5) + ((Mental * 10) * 0.8) + EKPlayer->GetCurrentWeapon()->WeaponAdditionalDamage;
	}
}

#pragma endregion

#pragma region LevelUp

void UEKPlayerStatusComponent::LevelUp(uint8 SetData)
{
	Level = FMath::Clamp(Level + SetData, 0, PlayerMaxLevel);
}

void UEKPlayerStatusComponent::LevelUpVitality(uint8 SetData)
{
	Vitality = FMath::Clamp(Vitality + SetData, 0, PlayerMaxVitalityLevel);
	SetMaxHp(0);
}

void UEKPlayerStatusComponent::LevelUpMental(uint8 SetData)
{
	Mental = FMath::Clamp(Mental + SetData, 0, PlayerMaxMentalLevel);
	SetMaxMp(0);
}

void UEKPlayerStatusComponent::LevelUpEndurance(uint8 SetData)
{
	Endurance = FMath::Clamp(Endurance + SetData, 0, PlayerMaxEnduranceLevel);
	SetMaxStamina(0);
}

void UEKPlayerStatusComponent::LevelUpStrength(uint8 SetData)
{
	Strength = FMath::Clamp(Strength + SetData, 0, PlayerMaxStrengthLevel);
	SetPlayerFinalDamage();
}

void UEKPlayerStatusComponent::LevelUpAbility(uint8 SetData)
{
	Ability = FMath::Clamp(Ability + SetData, 0, PlayerMaxAbilityLevel);
	SetPlayerFinalDamage();
}

void UEKPlayerStatusComponent::LevelUpIntelligence(uint8 SetData)
{
	Intelligence = FMath::Clamp(Intelligence + SetData, 0, PlayerMaxInteligenceLevel);
	SetPlayerFinalDamage();
}

#pragma endregion