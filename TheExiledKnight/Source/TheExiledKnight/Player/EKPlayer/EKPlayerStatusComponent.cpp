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