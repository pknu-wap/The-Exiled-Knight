// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "EKAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UEKAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UEKAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
