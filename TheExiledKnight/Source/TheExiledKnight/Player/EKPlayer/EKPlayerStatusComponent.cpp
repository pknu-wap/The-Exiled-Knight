// Made by Somalia Pirate


#include "EKPlayerStatusComponent.h"
#include "EKPlayer.h"
#include "EKPlayerController.h"

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
		SetStamina(2);
	}
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
}

void UEKPlayerStatusComponent::SetMaxMp(int32 SetData)
{
	MaxMp = FMath::Clamp(MaxMp + SetData, 0, PlayerMaxMp);
}

void UEKPlayerStatusComponent::SetMp(int32 SetData)
{
	Mp = FMath::Clamp(Mp + SetData, 0, MaxMp);
}

void UEKPlayerStatusComponent::SetMaxStamina(int32 SetData)
{
	MaxStamina = FMath::Clamp(MaxStamina + SetData, 0, PlayerMaxStamina);
}

void UEKPlayerStatusComponent::SetStamina(int32 SetData)
{
	Stamina = FMath::Clamp(Stamina + SetData, 0, MaxStamina);
}

uint32 UEKPlayerStatusComponent::GetPlayerDefaultDamage()
{
	return DefaultDamage;
}

uint32 UEKPlayerStatusComponent::GetPlayerFinalDamage()
{
	return FinalDamage;
}