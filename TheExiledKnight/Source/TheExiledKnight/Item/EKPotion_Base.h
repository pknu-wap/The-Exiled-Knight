// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/EKItem_Base.h"
#include "EKPotion_Base.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API AEKPotion_Base : public AEKItem_Base
{
	GENERATED_BODY()
	
public:
	virtual void UseItem() override;
};
