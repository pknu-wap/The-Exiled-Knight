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

	uint32 GetGreatSwordEnhancedCombo();
	void SetGreatSwordEnhancedCombo();
	void ResetGreatSwordEnhancedCombo();

	uint32 GetSpearEnhancedCombo();
	void SetSpearEnhancedCombo();
	void ResetSpearEnhancedCombo();

	uint32 GetStaffEnhancedCombo();
	void SetStaffEnhancedCombo();
	void ResetStaffEnhancedCombo();

public:
	bool bCanStaminaRecovery = true;

protected:
	UPROPERTY()
	TObjectPtr<class AEKPlayer> EKPlayer;

	UPROPERTY()
	TObjectPtr<class AEKPlayerController> EKPlayerController;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 DefaultDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statment|Basic")
	int32 FinalDamage;

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
