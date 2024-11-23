// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SanctuarySubsystem.generated.h"

USTRUCT(BlueprintType)
struct FSanctuaryStruct : public FTableRowBase
{
	GENERATED_BODY()

	FSanctuaryStruct() { };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int SanctuaryID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MapName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MapName_Korean;
};

UCLASS()
class THEEXILEDKNIGHT_API USanctuarySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable)
	void ActivateSanctuary(int SanctuaryID);

	UFUNCTION(BlueprintCallable)
	bool IsActivated(int SanctuaryID);

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<int> ActivatedSanctuary;

	UPROPERTY(BlueprintReadOnly)
	TMap<int, FSanctuaryStruct> SanctuaryMap;

private:
	UDataTable* SanctuaryDB;

};
