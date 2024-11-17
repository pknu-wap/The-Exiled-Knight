// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyWeapon/EKEnemyEnergyBeam.h"

// Sets default values
AEKEnemyEnergyBeam::AEKEnemyEnergyBeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEKEnemyEnergyBeam::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEKEnemyEnergyBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

