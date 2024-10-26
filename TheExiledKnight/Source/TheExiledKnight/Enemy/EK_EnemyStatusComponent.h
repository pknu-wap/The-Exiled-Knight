// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EK_EnemyStatusComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THEEXILEDKNIGHT_API UEK_EnemyStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UEK_EnemyStatusComponent();
	UFUNCTION(BlueprintCallable)
	uint8 GetPosieLevel();
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth();
	UFUNCTION(BlueprintCallable)
	float GetMaxPoise();
	UFUNCTION(BlueprintCallable)
	float  GetCurrentPoise();
	UFUNCTION(BlueprintCallable)
	bool  GetIsDead();
	
	UFUNCTION(BlueprintCallable)
	void SetPoiseLevel(uint8 amount);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float amount);

	UFUNCTION(BlueprintCallable)
	void SetCurrentHealth(float amount);

	UFUNCTION(BlueprintCallable)
	void SetMaxPoise(float amount);

	UFUNCTION(BlueprintCallable)
	void SetCurrentPoise(float amount);

	UFUNCTION(BlueprintCallable)
	void SetIsDead(bool isDead);

	UFUNCTION(BlueprintCallable)

	virtual void TakeDamage(float amount);
	
	FOnHPIsZeroDelegate OnHPIsZero;
private:
	UPROPERTY(VisibleAnywhere,Category=Stat,Meta  =(AllowPrivteAccess=true))
	uint8 PoiseLevel;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))

	float MaxHealth;
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))

	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))

	float MaxPosie;
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))

	float CurrentPosie;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivteAccess = true))

	bool bIsDead;

	


};
