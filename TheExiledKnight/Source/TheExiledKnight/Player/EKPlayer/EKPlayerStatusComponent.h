// Made by Somalia Pirate

#pragma once

#include "Components/ActorComponent.h"
#include "EKPlayerStatusComponent.generated.h"

#define PlayerMaxHp 10000
#define PlayerMaxMp 10000
#define PlayerMaxStamina 10000

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHpUpdated, int32, MaxHP, int32, CurrentHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaUpdated, int32, MaxStamina, int32, CurrentStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMpUpdated, int32, MaxMP, int32, CurrentMP);

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
	uint32 GetMaxHp();
	uint32 GetHp();
	uint32 GetMaxMp();
	uint32 GetMp();
	uint32 GetMaxStamina();
	uint32 GetStamina();

	void SetMaxHp(int32 SetData);
	void SetHp(int32 SetData);
	void SetMaxMp(int32 SetData);
	void SetMp(int32 SetData);
	void SetMaxStamina(int32 SetData);
	void SetStamina(int32 SetData);

public:
	uint32 GetPlayerDefaultDamage();
	void SetPlayerDefaultDamage();
	uint32 GetPlayerFinalDamage();
	void SetPlayerFinalDamage();

	void LevelUp();
	void LevelUpVitality();
	void LevelUpMental();
	void LevelUpEndurance();
	void LevelUpStrength();
	void LevelUpAbility();
	void LevelUpIntelligence();

	// About Weapon Attack Combo
	uint32 GetGreatSwordCombo();
	void SetGreatSwordCombo();
	void ResetGreatSwordCombo();

	uint32 GetSpearCombo();
	void SetSpearCombo();
	void ResetSpearCombo();

	uint32 GetStaffCombo();
	void SetStaffCombo();
	void ResetStaffCombo();

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

protected:
	UPROPERTY()
	uint32 GreatSwordCombo = 1;

	UPROPERTY()
	uint32 SpearCombo = 1;

	UPROPERTY()
	uint32 StaffCombo = 1;
};
