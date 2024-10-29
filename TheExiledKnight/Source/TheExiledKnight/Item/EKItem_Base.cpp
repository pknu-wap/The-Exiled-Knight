// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EKItem_Base.h"

// Sets default values
AEKItem_Base::AEKItem_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AEKItem_Base::AEKItem_Base(FName RowName)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//FItemStruct* InitItem;
	//InitItem = ItemDB->FindRow<FItemStruct>(RowName, TEXT("Item"));

	//ItemInfo = *InitItem;

	ItemInfo = *(ItemDB->FindRow<FItemStruct>(RowName, TEXT("Item")));
}

// Called when the game starts or when spawned
void AEKItem_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEKItem_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

