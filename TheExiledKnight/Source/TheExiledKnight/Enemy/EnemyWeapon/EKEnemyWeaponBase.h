// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EKEnemyWeaponBase.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AEKEnemyWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEKEnemyWeaponBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh");
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBox;

};
