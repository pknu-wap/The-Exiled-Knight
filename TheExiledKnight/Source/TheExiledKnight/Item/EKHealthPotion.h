// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/EKPotion_Base.h"
#include "EKHealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API AEKHealthPotion : public AEKPotion_Base
{
	GENERATED_BODY()

public:
	AEKHealthPotion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void UseItem(UWorld* WorldContext, int level) override;
};
