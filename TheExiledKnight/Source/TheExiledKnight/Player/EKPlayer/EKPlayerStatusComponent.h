// Made by Somalia Pirate

#pragma once

#include "Components/ActorComponent.h"
#include "EKPlayerStatusComponent.generated.h"

#define PlayerMaxHp 10000
#define PlayerMaxMp 10000
#define PlayerMaxStamina 10000

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPUpdated, int32, MaxHP, int32, CurrentHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaUpdated, int32, MaxStamina, int32, CurrentStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMPUpdated, int32, MaxMP, int32, CurrentMP);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UEKPlayerStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEKPlayerStatusComponent();

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void TakeDamage(float Damage);

public:
	uint32 GetMaxHp() { return MaxHp; }
	uint32 GetHp() { return Hp; }
	uint32 GetMaxMp() { return MaxMp; }
	uint32 GetMp() { return Mp; }
	uint32 GetMaxStamina() { return MaxStamina; }
	uint32 GetStamina() { return Stamina; }

	void SetMaxHp(int32 SetData);
	void SetHp(int32 SetData);
	void SetMaxMp(int32 SetData);
	void SetMp(int32 SetData);
	void SetMaxStamina(int32 SetData);
	void SetStamina(int32 SetData);

public:
	uint32 GetPlayerDefaultDamage() { return DefaultDamage; }
	void SetPlayerDefaultDamage();
	uint32 GetPlayerFinalDamage() { return FinalDamage; }
	void SetPlayerFinalDamage();

	void LevelUp();
	void LevelUpVitality();
	void LevelUpMental();
	void LevelUpEndurance();
	void LevelUpStrength();
	void LevelUpAbility();
	void LevelUpIntelligence();

public:
	bool bCanStaminaRecovery = true;

protected:
	UPROPERTY()
	TObjectPtr<class AEKPlayer> EKPlayer;

	UPROPERTY()
	TObjectPtr<class AEKPlayerController> EKPlayerController;

protected:
	// Basic status
	UPROPERTY(VisibleAnywhere, Category = "Statment|Basic")
	uint32 MaxHp;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Basic")
	uint32 Hp;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Basic")
	uint32 MaxMp;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Basic")
	uint32 Mp;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Basic")
	uint32 MaxStamina;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Basic")
	uint32 Stamina;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Basic")
	uint32 DefaultDamage;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Basic")
	uint32 FinalDamage;

protected:
	// Upgrade status
	UPROPERTY(VisibleAnywhere, Category = "Statment|Upgrade")
	uint32 MaxLevel;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Upgrade")
	uint32 Level;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Upgrade")
	uint32 Vitality;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Upgrade")
	uint32 Mental;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Upgrade")
	uint32 Endurance;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Upgrade")
	uint32 Strength;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Upgrade")
	uint32 Ability;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Upgrade")
	uint32 Intelligence;

public:
	UPROPERTY(BlueprintAssignable)
	FOnHPUpdated Delegate_HPUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnMPUpdated Delegate_MPUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnStaminaUpdated Delegate_StaminaUpdated;
};
