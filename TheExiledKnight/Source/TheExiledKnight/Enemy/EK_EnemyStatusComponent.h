// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EK_EnemyStatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHPIsZero);  
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageTaken);    
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHitAnimationEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPoiseIsZero); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStunAnimationEnd);
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) 

class THEEXILEDKNIGHT_API UEK_EnemyStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UEK_EnemyStatusComponent();


	void SetPoise(float amount);
	void SetHealth(float amount);
	void SetAttackDamage(float amount);
	void SetIsDead(bool isDead);
	void  DamageCurrentPoise(float amount);
	void DamageCurrentHealth(float amount); 
	void ResetCurrentPoise();
	
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

	UPROPERTY(BlueprintAssignable, Category = "Status")
	FOnHitAnimationEnd OnHurtAnimationEnd; 

	UPROPERTY(BlueprintAssignable, Category = "Status")
	FOnPoiseIsZero OnPoiseIsZero;

	UPROPERTY(BlueprintAssignable, Category = "Status")
	FOnStunAnimationEnd OnStunAnimationEnd;
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
