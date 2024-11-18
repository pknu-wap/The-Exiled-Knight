// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "EKDamageType.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UEKDamageType : public UDamageType
{
	GENERATED_BODY() 
	
};
UCLASS()
class THEEXILEDKNIGHT_API UEKNormalDamageType : public UEKDamageType
{
	GENERATED_BODY()
};

UCLASS()
class THEEXILEDKNIGHT_API UEKStrongDamageType : public UEKDamageType
{
	GENERATED_BODY()
};
