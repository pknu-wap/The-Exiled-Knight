// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagsManager.h"
#include "UISubsystem.generated.h"

USTRUCT(BlueprintType)
struct FTagWidgetStruct
{
	GENERATED_BODY()

	FTagWidgetStruct() {}
	FTagWidgetStruct(FGameplayTag InTag, UUserWidget* InWidget) : Tag(InTag), Widget(InWidget)
	{}

	FGameplayTag Tag;
	UUserWidget* Widget;
};

UCLASS()
class THEEXILEDKNIGHT_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	UFUNCTION(BlueprintCallable)
	void RegisterLayer(FGameplayTag LayerTag, UUserWidget* Widget);

	UFUNCTION(BlueprintCallable)
	void UnRegisterLayer(FGameplayTag LayerTag);

	UFUNCTION()
	void RemoveWidget(FGameplayTag WidgetTag);

	UFUNCTION(BlueprintCallable)
	void SetWidgetVisibility(FGameplayTag WidgetTag, ESlateVisibility Visibility);

private:
	// Layers Map
	TMap<FGameplayTag, UUserWidget*> LayerMap;

	// All Widgets Map
	TMap<FGameplayTag, UUserWidget*> WidgetMap;
};
