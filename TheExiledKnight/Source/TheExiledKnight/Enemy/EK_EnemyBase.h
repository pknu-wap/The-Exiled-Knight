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

protected:
	// Called when the game starts or when spawned


public:	
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UEK_EnemyStatusComponent* EnemyStat;
	
	virtual void AttackHitCheck();

	virtual void SetAttackHitCheck(bool check);
	virtual bool GetAttackHitCheck();
private:
	
	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	float  AttackRadius;
	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	float AttackHalfHeight;
	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivteAccess = true))
	bool bAttackHitCheck;
};
