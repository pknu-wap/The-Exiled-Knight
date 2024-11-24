// Made by Somalia Pirate

#include "EKPlayerStatusComponent.h"
#include "../Weapon/EKPlayerWeapon.h"
#include "../EKPlayerGameplayTags.h"
#include "Components/SlotComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/InventorySubsystem.h"

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
	Vitality = 1; BaseVitality = 1;
	Mental = 1;	BaseMental = 1;
	Endurance = 1; BaseEndurance = 1;
	Strength = 1; BaseStrength = 1;
	Ability = 1; BaseAbility = 1;
	Intelligence = 1; BaseIntelligence = 1;
}


void UEKPlayerStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	EKPlayer = Cast<AEKPlayer>(GetOwner());

	if (EKPlayer)
	{
		EKPlayerController = Cast<AEKPlayerController>(EKPlayer->GetController());
	}

	EKPlayerGameInstance = Cast<UEKPlayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (EKPlayerGameInstance)
	{
		FEKPlayerLevel* EKPlayerLevelTemp = EKPlayerGameInstance->GetEKPlayerLevelData(Level);
		EKPlayerLevelData = *EKPlayerLevelTemp;

		FEKPlayerStatus* EKPlayerStatusTemp = EKPlayerGameInstance->GetEKPlayerStatusData(Level);
		EKPlayerStatusData = *EKPlayerStatusTemp;
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

void UEKPlayerStatusComponent::SetMaxHp(int32 VitalityLevel)
{
	if (!EKPlayerGameInstance)
	{
		return;
	}

	FEKPlayerStatus* EKPlayerStatusTemp = EKPlayerGameInstance->GetEKPlayerStatusData(VitalityLevel);
	EKPlayerStatusData = *EKPlayerStatusTemp;

	MaxHp = FMath::Clamp(EKPlayerStatusData.Vitality, 0, PlayerMaxHp);
	SetHp(MaxHp);
}

void UEKPlayerStatusComponent::SetHp(int32 SetData)
{
	Hp = FMath::Clamp(Hp + SetData, 0, MaxHp);
	Delegate_HPUpdated.Broadcast(MaxHp, Hp);
}

void UEKPlayerStatusComponent::SetMaxMp(int32 MentalLevel)
{
	if (!EKPlayerGameInstance)
	{
		return;
	}

	FEKPlayerStatus* EKPlayerStatusTemp = EKPlayerGameInstance->GetEKPlayerStatusData(MentalLevel);
	EKPlayerStatusData = *EKPlayerStatusTemp;

	MaxMp = FMath::Clamp(EKPlayerStatusData.Mental, 0, PlayerMaxMp);
	SetMp(MaxMp);
}

void UEKPlayerStatusComponent::SetMp(int32 SetData)
{
	Mp = FMath::Clamp(Mp + SetData, 0, MaxMp);
	Delegate_MPUpdated.Broadcast(MaxMp, Mp);
}

void UEKPlayerStatusComponent::SetMaxStamina(int32 EnduranceLevel)
{
	if (!EKPlayerGameInstance)
	{
		return;
	}

	FEKPlayerStatus* EKPlayerStatusTemp = EKPlayerGameInstance->GetEKPlayerStatusData(EnduranceLevel);
	EKPlayerStatusData = *EKPlayerStatusTemp;

	MaxStamina = FMath::Clamp(EKPlayerStatusData.Endurance, 0, PlayerMaxStamina);
	SetStamina(MaxStamina);
}

void UEKPlayerStatusComponent::SetStamina(int32 SetData)
{
	Stamina = FMath::Clamp(Stamina + SetData, 0, MaxStamina);
	Delegate_StaminaUpdated.Broadcast(MaxStamina, Stamina);
}

void UEKPlayerStatusComponent::Recalculate_Status()
{
	Calculate_NormalStatus();
	Calculate_BasicStatus();
}

void UEKPlayerStatusComponent::Calculate_BasicStatus()
{
	MaxHp = 1000 + Vitality * 100;
	MaxMp = 1000 + Mental * 100;
	Stamina = 1000 + Endurance * 100;

	UInventorySubsystem* invSystem = GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	if (!invSystem) return;
	APlayerController* pc = UGameplayStatics::GetPlayerController(this, 0);
	if (!pc) return;
	USlotComponent* slotComp = pc->GetComponentByClass<USlotComponent>();
	if (!slotComp) return;

	// Calculate Weapon Stat
	FWeaponStruct* weaponInfo = invSystem->GetWeaponInfo(slotComp->WeaponSlots[slotComp->ActiveWeaponSlot].ID);
	if (!weaponInfo) return;
	ATK = weaponInfo->AttackPow;

	// Calculate 
	ATK *= 1 + 0.02 * Strength;
}

void UEKPlayerStatusComponent::Calculate_NormalStatus()
{
	// Calculate Rune Stat
	UInventorySubsystem* invSystem = GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	if (!invSystem) return;
	APlayerController* pc = UGameplayStatics::GetPlayerController(this, 0);
	if (!pc) return;
	USlotComponent* slotComp = pc->GetComponentByClass<USlotComponent>();
	if (!slotComp) return;

	for (int i = 0; i < slotComp->RuneSlots.Num(); i++)
	{
		int itemID = slotComp->RuneSlots[i].ID;
		if (itemID > 0)
		{
			FRune* runeInfo = invSystem->GetRuneInfo(itemID);
			if (!runeInfo) return;

			Vitality = BaseVitality + runeInfo->Vitality;
			Mental = BaseMental + runeInfo->Mental;
			Endurance = BaseEndurance + runeInfo->Endurance;
			Strength = BaseStrength + runeInfo->Strength;
			Ability = BaseAbility + runeInfo->Ability;
			Intelligence = BaseIntelligence + runeInfo->Intelligence;
		}
	}
}

#pragma endregion

#pragma region Damage

void UEKPlayerStatusComponent::SetPlayerFinalDamage()
{
	if (!EKPlayerGameInstance)
	{
		return;
	}

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_GreatSword))
	{
		FEKPlayerStatus* EKPlayerStatusTemp = EKPlayerGameInstance->GetEKPlayerStatusData(BaseStrength);
		EKPlayerStatusData = *EKPlayerStatusTemp;
		FinalDamage = DefaultDamage + EKPlayerStatusData.Strength + EKPlayer->GetCurrentWeapon()->WeaponAdditionalDamage;
	}
	else if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Spear))
	{
		FEKPlayerStatus* EKPlayerStatusTemp = EKPlayerGameInstance->GetEKPlayerStatusData(BaseAbility);
		EKPlayerStatusData = *EKPlayerStatusTemp;
		FinalDamage = DefaultDamage + EKPlayerStatusData.Ability + EKPlayer->GetCurrentWeapon()->WeaponAdditionalDamage;
	}
	else if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Staff))
	{
		FEKPlayerStatus* EKPlayerStatusTemp = EKPlayerGameInstance->GetEKPlayerStatusData(BaseIntelligence);
		EKPlayerStatusData = *EKPlayerStatusTemp;
		FinalDamage = DefaultDamage + EKPlayerStatusData.Intelligence + EKPlayer->GetCurrentWeapon()->WeaponAdditionalDamage;
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
	BaseVitality = FMath::Clamp(BaseVitality + SetData, 0, PlayerMaxVitalityLevel);
	SetMaxHp(BaseVitality);
}

void UEKPlayerStatusComponent::LevelUpMental(uint8 SetData)
{
	BaseMental = FMath::Clamp(BaseMental + SetData, 0, PlayerMaxMentalLevel);
	SetMaxMp(BaseMental);
}

void UEKPlayerStatusComponent::LevelUpEndurance(uint8 SetData)
{
	BaseEndurance = FMath::Clamp(BaseEndurance + SetData, 0, PlayerMaxEnduranceLevel);
	SetMaxStamina(BaseEndurance);
}

void UEKPlayerStatusComponent::LevelUpStrength(uint8 SetData)
{
	BaseStrength = FMath::Clamp(BaseStrength + SetData, 0, PlayerMaxStrengthLevel);
	SetPlayerFinalDamage();
}

void UEKPlayerStatusComponent::LevelUpAbility(uint8 SetData)
{
	BaseAbility = FMath::Clamp(BaseAbility + SetData, 0, PlayerMaxAbilityLevel);
	SetPlayerFinalDamage();
}

void UEKPlayerStatusComponent::LevelUpIntelligence(uint8 SetData)
{
	BaseIntelligence = FMath::Clamp(BaseIntelligence + SetData, 0, PlayerMaxInteligenceLevel);
	SetPlayerFinalDamage();
}

#pragma endregion