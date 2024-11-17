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
	MaxHp = 100;
	Hp = 50;
	MaxMp = 100;
	Mp = 50;
	MaxStamina = 1000;
	Stamina = 1000;
	DefaultDamage = 1.0f;
	FinalDamage = DefaultDamage;
	
	// Edit Basic Status Value Here
	Level = 6;
	Vitality = 1;
	Mental = 1;
	Endurance = 1;
	Strength = 1;
	Ability = 1;
	Intelligence = 1;
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
	MaxHp = FMath::Clamp(MaxHp + SetData, 0, PlayerMaxHp);
}

void UEKPlayerStatusComponent::SetHp(int32 SetData)
{
	Hp = FMath::Clamp(Hp + SetData, 0, MaxHp);
	Delegate_HPUpdated.Broadcast(MaxHp, Hp);
}

void UEKPlayerStatusComponent::SetMaxMp(int32 SetData)
{
	MaxMp = FMath::Clamp(MaxMp + SetData, 0, PlayerMaxMp);
}

void UEKPlayerStatusComponent::SetMp(int32 SetData)
{
	Mp = FMath::Clamp(Mp + SetData, 0, MaxMp);
	Delegate_MPUpdated.Broadcast(MaxMp, Mp);
}

void UEKPlayerStatusComponent::SetMaxStamina(int32 SetData)
{
	MaxStamina = FMath::Clamp(MaxStamina + SetData, 0, PlayerMaxStamina);
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
}

void UEKPlayerStatusComponent::LevelUpMental(uint8 SetData)
{
	Mental = FMath::Clamp(Mental + SetData, 0, PlayerMaxMentalLevel);
}

void UEKPlayerStatusComponent::LevelUpEndurance(uint8 SetData)
{
	Endurance = FMath::Clamp(Endurance + SetData, 0, PlayerMaxEnduranceLevel);
}

void UEKPlayerStatusComponent::LevelUpStrength(uint8 SetData)
{
	Strength = FMath::Clamp(Strength + SetData, 0, PlayerMaxStrengthLevel);
}

void UEKPlayerStatusComponent::LevelUpAbility(uint8 SetData)
{
	Ability = FMath::Clamp(Ability + SetData, 0, PlayerMaxAbilityLevel);
}

void UEKPlayerStatusComponent::LevelUpIntelligence(uint8 SetData)
{
	Intelligence = FMath::Clamp(Intelligence + SetData, 0, PlayerMaxInteligenceLevel);
}

#pragma endregion