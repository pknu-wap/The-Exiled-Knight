// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Sanctuary/EKSanctuary.h"
#include "NiagaraComponent.h"

// Sets default values
AEKSanctuary::AEKSanctuary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SMComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SMComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Niagara_Santuary = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	Niagara_Santuary->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AEKSanctuary::BeginPlay()
{
	Super::BeginPlay();
	
	ActivateSantuary();
}

// Called every frame
void AEKSanctuary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEKSanctuary::ActivateSantuary()
{
	GetWorld()->GetTimerManager().SetTimer(ActivateHandle, 
		[&]() { 
			CurrentScale = CurrentScale + FVector(0.05, 0.05, 0.05);
			Niagara_Santuary->SetWorldScale3D(CurrentScale);
		},
		0.02, true);

	GetWorld()->GetTimerManager().SetTimer(StopHandle,
		[&]() { 
			GetWorld()->GetTimerManager().ClearTimer(ActivateHandle);
			// ActivateHandle.Invalidate();
		}, 1, false);
}

