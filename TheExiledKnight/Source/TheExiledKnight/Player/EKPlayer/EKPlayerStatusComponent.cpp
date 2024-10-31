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
	DefaultDamage = 0;
	FinalDamage = 0;

	// Edit Basic Status Value Here
	MaxLevel = 100;
	Level = 1;
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

	if (bCanStaminaRecovery)
	{
		SetStamina(4);
	}
}

void UEKPlayerStatusComponent::TakeDamage(float Damage)
{
	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Hit))
	{
		return;
	}

	SetHp(-Damage);
	EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Hit);
	EKPlayer->GetCurrentWeapon()->PlayHitAnimMontage(EKPlayer, EKPlayerController);
}

uint32 UEKPlayerStatusComponent::GetMaxHp()
{
	return MaxHp;
}

uint32 UEKPlayerStatusComponent::GetHp()
{
	return Hp;
}

uint32 UEKPlayerStatusComponent::GetMaxMp()
{
	return MaxMp;
}

uint32 UEKPlayerStatusComponent::GetMp()
{
	return Mp;
}

uint32 UEKPlayerStatusComponent::GetMaxStamina()
{
	return MaxStamina;
}

uint32 UEKPlayerStatusComponent::GetStamina()
{
	return Stamina;
}

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

uint32 UEKPlayerStatusComponent::GetPlayerDefaultDamage()
{
	return DefaultDamage;
}

uint32 UEKPlayerStatusComponent::GetPlayerFinalDamage()
{
	return FinalDamage;
}

// About Weapon Attack Combo

uint32 UEKPlayerStatusComponent::GetGreatSwordCombo()
{
	return GreatSwordCombo;
}

void UEKPlayerStatusComponent::SetGreatSwordCombo()
{
	if (GreatSwordCombo < 3)
	{
		GreatSwordCombo++;
	}
	else
	{
		ResetGreatSwordCombo();
	}
}

void UEKPlayerStatusComponent::ResetGreatSwordCombo()
{
	GreatSwordCombo = 1;
}

uint32 UEKPlayerStatusComponent::GetSpearCombo()
{
	return SpearCombo;
}

void UEKPlayerStatusComponent::SetSpearCombo()
{
	if (SpearCombo < 5)
	{
		SpearCombo++;
	}
	else
	{
		ResetSpearCombo();
	}
}

void UEKPlayerStatusComponent::ResetSpearCombo()
{
	SpearCombo = 1;
}

uint32 UEKPlayerStatusComponent::GetStaffCombo()
{
	return StaffCombo;
}

void UEKPlayerStatusComponent::SetStaffCombo()
{
	if (StaffCombo < 5)
	{
		StaffCombo++;
	}
	else
	{
		ResetStaffCombo();
	}
}

void UEKPlayerStatusComponent::ResetStaffCombo()
{
	StaffCombo = 1;
}

uint32 UEKPlayerStatusComponent::GetGreatSwordEnhancedCombo()
{
	return GreatSwordEnhancedCombo;
}

void UEKPlayerStatusComponent::SetGreatSwordEnhancedCombo()
{
	if (GreatSwordEnhancedCombo < 2)
	{
		GreatSwordEnhancedCombo++;
	}
	else
	{
		ResetGreatSwordEnhancedCombo();
	}
}

void UEKPlayerStatusComponent::ResetGreatSwordEnhancedCombo()
{
	GreatSwordEnhancedCombo = 1;
}

uint32 UEKPlayerStatusComponent::GetSpearEnhancedCombo()
{
	return SpearEnhancedCombo;
}

void UEKPlayerStatusComponent::SetSpearEnhancedCombo()
{
	if (SpearEnhancedCombo < 5)
	{
		SpearEnhancedCombo++;
	}
	else
	{
		ResetSpearEnhancedCombo();
	}
}

void UEKPlayerStatusComponent::ResetSpearEnhancedCombo()
{
	SpearEnhancedCombo = 1;
}

uint32 UEKPlayerStatusComponent::GetStaffEnhancedCombo()
{
	return StaffEnhancedCombo;
}

void UEKPlayerStatusComponent::SetStaffEnhancedCombo()
{
	if (StaffEnhancedCombo < 5)
	{
		StaffEnhancedCombo++;
	}
	else
	{
		ResetStaffEnhancedCombo();
	}
}

void UEKPlayerStatusComponent::ResetStaffEnhancedCombo()
{
	StaffEnhancedCombo = 1;
}