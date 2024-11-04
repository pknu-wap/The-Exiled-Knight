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

	UFUNCTION(BlueprintCallable)
	void SetMaxPoise(float amount);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float amount);

	UFUNCTION(BlueprintCallable)
	void SetIsDead(bool isDead);

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	float GetMaxPoise();

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth();

	UFUNCTION(BlueprintCallable)
	float GetCurrentPoise();
	
	UFUNCTION(BlueprintCallable)
	bool  GetIsDead();


	UFUNCTION(BlueprintCallable)
	void  ChangeCurrentPoise(float amount);

	UFUNCTION(BlueprintCallable)
	void ChangeCurrentHealth(float amount);

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
	float MaxPosie;
	
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))
	float CurrentPoise;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))
	bool bIsDead;

};
