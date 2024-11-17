// Made by Somalia Pirate

#pragma once

#include "Components/ActorComponent.h"
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
	TObjectPtr<class AEKPlayer> EKPlayer;

	UPROPERTY()
	TObjectPtr<class AEKPlayerController> EKPlayerController;

#pragma region Basic Status

protected:
	// Basic status
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 MaxHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 Hp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 MaxMp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 Mp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 Stamina;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Basic")
	float DefaultDamage;

	UPROPERTY(VisibleAnywhere, Category = "Statment|Basic")
	float FinalDamage;

#pragma endregion

#pragma region Upgrade Status

protected:
	// Upgrade status
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 MaxLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 Level;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 Vitality;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 Mental;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 Endurance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 Strength;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 Ability;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 Intelligence;

protected:
	UPROPERTY()
	int32 GreatSwordCombo = 1;

	UPROPERTY()
	int32 SpearCombo = 1;

	UPROPERTY()
	int32 StaffCombo = 1;

	UPROPERTY()
	int32 GreatSwordEnhancedCombo = 1;

	UPROPERTY()
	int32 SpearEnhancedCombo = 1;

	UPROPERTY()
	int32 StaffEnhancedCombo = 1;

public:
	UPROPERTY(BlueprintAssignable)
	FOnHPUpdated Delegate_HPUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnMPUpdated Delegate_MPUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnStaminaUpdated Delegate_StaminaUpdated;
};
