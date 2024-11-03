// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EK_EnemyBase.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AEK_EnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEK_EnemyBase(); 

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInvestigator, AActor* DmageCauser)override;
	
protected:

	

public:	
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UEK_EnemyStatusComponent* EnemyStat;
	
	virtual TObjectPtr <UEK_EnemyStatusComponent> GetStatusComponent();
	
private:
	
	
};
