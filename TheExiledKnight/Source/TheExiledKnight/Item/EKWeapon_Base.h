// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/EKItem_Base.h"
#include "EKWeapon_Base.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API AEKWeapon_Base : public AEKItem_Base
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEKWeapon_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual const uint8 GetItemID() { return ID; }
	virtual const FItemStruct GetItemInfo() { return ItemInfo; }
	virtual const uint8 GetItemQuantity() { return Quantity; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float STRRate = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float DEXRate = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float INTRate = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	int Level = 1;

	// Skill (AnimMontage), WeaponType, 스탯에 따른 보정 수치(근력, 기량, 지력), 강화 레벨
	
};
