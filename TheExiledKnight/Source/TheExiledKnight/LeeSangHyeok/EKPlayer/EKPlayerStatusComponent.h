// Made by Somalia Pirate

#pragma once

#include "Components/ActorComponent.h"
#include "EKPlayerStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEKPlayerStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEKPlayerStatusComponent();

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void GetPlayerDefaultDamage();
	void SetPlayerDefaultDamage();
	void GetPlayerFinalDamage();
	void SetPlayerFinalDamage();

	void LevelUpVitality();
	void LevelUpMental();
	void LevelUpEndurance();
	void LevelUpStrength();
	void LevelUpAbility();
	void LevelUpIntelligence();

protected:
	// Basic status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Basic")
	uint8 MaxHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Basic")
	uint8 Hp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Basic")
	uint8 MaxMp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Basic")
	uint8 Mp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Basic")
	uint8 MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Basic")
	uint8 Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Basic")
	uint8 DefaultDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Basic")
	uint8 FinalDamage;
protected:
	// Upgrade status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Upgrade")
	uint8 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Upgrade")
	uint8 MaxLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Upgrade")
	uint8 Vitality;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Upgrade")
	uint8 Mental;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Upgrade")
	uint8 Endurance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Upgrade")
	uint8 Strength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Upgrade")
	uint8 Ability;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statment|Upgrade")
	uint8 Intelligence;
};
