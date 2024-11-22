// Made by Somalia Pirate

#pragma once

#include "Components/ActorComponent.h"
#include "EKPlayer.h"
#include "EKPlayerController.h"
#include "Player/GameInstance/EKPlayerGameInstance.h"
#include "EKPlayerStatusComponent.generated.h"

#pragma region Max Value

// Edit Player Basic Max Stat Here
#define PlayerMaxHp 10000
#define PlayerMaxMp 10000
#define PlayerMaxStamina 10000

// Edit Player Max Level Here
#define PlayerMaxLevel 120
#define PlayerMaxVitalityLevel 20
#define PlayerMaxMentalLevel 20
#define PlayerMaxEnduranceLevel 20
#define PlayerMaxStrengthLevel 20
#define PlayerMaxAbilityLevel 20
#define PlayerMaxInteligenceLevel 20

#pragma endregion

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
	void Recalculate_Status();
	void Calculate_BasicStatus();
	void Calculate_NormalStatus();

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
	float GetPlayerDefaultDamage() { return DefaultDamage; }
	void SetPlayerDefaultDamage();

	float GetPlayerFinalDamage() { return FinalDamage; }
	void SetPlayerFinalDamage();

	void LevelUp(uint8 SetData);
	void LevelUpVitality(uint8 SetData);
	void LevelUpMental(uint8 SetData);
	void LevelUpEndurance(uint8 SetData);
	void LevelUpStrength(uint8 SetData);
	void LevelUpAbility(uint8 SetData);
	void LevelUpIntelligence(uint8 SetData);

public:
	bool bCanStaminaRecovery = true;

protected:
	UPROPERTY()
	AEKPlayer* EKPlayer;

	UPROPERTY()
	AEKPlayerController* EKPlayerController;

	UPROPERTY()
	UEKPlayerGameInstance* EKPlayerGameInstance;

	UPROPERTY()
	FEKPlayerLevel EKPlayerLevel;

	UPROPERTY()
	FEKPlayerStatus EKPlayerStatus;

#pragma region Basic Status

protected:
	// Basic status
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int MaxHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int Hp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int MaxMp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int Mp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int ATK;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int DEF;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 CurrentSouls;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Basic")
	float DefaultDamage;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Basic")
	float FinalDamage;

#pragma endregion

#pragma region Upgrade Status

protected:
	// Upgrade status
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 Vitality;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 BaseVitality;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 Mental;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 BaseMental;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 Endurance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 BaseEndurance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 Strength;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 BaseStrength;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 Ability;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 BaseAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 Intelligence;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Upgrade")
	int32 BaseIntelligence;

#pragma endregion

public:
	UPROPERTY(BlueprintAssignable)
	FOnHPUpdated Delegate_HPUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnMPUpdated Delegate_MPUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnStaminaUpdated Delegate_StaminaUpdated;
};
