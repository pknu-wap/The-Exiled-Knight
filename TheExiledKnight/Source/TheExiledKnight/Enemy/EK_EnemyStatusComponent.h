// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EK_EnemyStatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHPIsZero);  
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageTaken);    
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) 

class THEEXILEDKNIGHT_API UEK_EnemyStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UEK_EnemyStatusComponent();


	void SetMaxPoise(float amount);
	void SetMaxHealth(float amount);
	void SetAttackDamage(float amount);
	void SetIsDead(bool isDead);
	void  ChangeCurrentPoise(float amount);
	void ChangeCurrentHealth(float amount); 
	
	float GetMaxHealth();
    float GetMaxPoise();
	float GetCurrentHealth();
	float GetCurrentPoise();
	float GetAttackDamage();
    bool  GetIsDead();
	
	UPROPERTY(BlueprintAssignable, Category = "Status")
	FOnDamageTaken OnDamageTaken;

	UPROPERTY(BlueprintAssignable, Category = "Status")
	FOnHPIsZero OnHPIsZero;

	
private:



	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))
	float CurrentHealth;
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))
	float MaxPoise;
	
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))
	float CurrentPoise;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))
	float AttackDamage;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))
	bool bIsDead;



};
