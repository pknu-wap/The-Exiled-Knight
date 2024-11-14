// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/ItemStruct.h"
#include "EKEnums.h"
#include "EKItem_Base.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AEKItem_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEKItem_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const uint8 GetItemID() { return ID; }
	const FItemStruct GetItemInfo() { return ItemInfo; }
	const uint8 GetItemQuantity() { return Quantity; }

	UFUNCTION(BlueprintCallable)
	virtual void UseItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	uint8 ID = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	FItemStruct ItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	uint8 Quantity = 1;
};
