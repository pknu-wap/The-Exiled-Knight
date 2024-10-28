// Fill out your copyright notice in the Description page of Project Settings.


#include "EKAssetManager.h"
#include "EKGameplayTags.h"

UEKAssetManager& UEKAssetManager::Get()
{
	check(GEngine);
	UEKAssetManager* EKAssetManager = Cast<UEKAssetManager>(GEngine->AssetManager);
	return *EKAssetManager;
}

void UEKAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FEKGameplayTags::InitializeNativeGameplayTags();
}
