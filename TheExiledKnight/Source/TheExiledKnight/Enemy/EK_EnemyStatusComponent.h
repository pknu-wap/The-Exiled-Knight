// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EK_EnemyStatusComponent.generated.h"



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
	virtual void TakeDamage(float amount);
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EnemyStat")
	uint8 PoiseLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStat")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStat")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStat")
	float MaxPosie;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStat")
	float CurrentPosie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStat")
	bool bIsDead;

	


};
