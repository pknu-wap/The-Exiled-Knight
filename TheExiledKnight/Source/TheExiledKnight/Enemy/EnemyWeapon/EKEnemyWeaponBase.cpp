// Fill out your copyright notice in the Description page of Project Settings.


#include "EKEnemyWeaponBase.h"
#include"Components/BoxComponent.h"


// Sets default values
AEKEnemyWeaponBase::AEKEnemyWeaponBase()
{
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
    RootComponent = CollisionBox;

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetCollisionProfileName(FName("NoCollision"));
    WeaponMesh->SetupAttachment(RootComponent); 
}


