// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"Engine/DataTable.h"
#include"EKEnemyData.generated.h"


USTRUCT(BlueprintType)
struct FEnemyData :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName Enemy_ID;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	FName EnemyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float  CurrentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float SightRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float HearingRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropSouls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName  DropItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool bIsBoss;
};