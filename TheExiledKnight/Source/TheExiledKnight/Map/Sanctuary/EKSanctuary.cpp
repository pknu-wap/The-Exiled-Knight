// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Sanctuary/EKSanctuary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/EK_EnemyBase.h"
#include "Subsystems/SanctuarySubsystem.h"

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

	USanctuarySubsystem* sanctuarySystem = GetGameInstance()->GetSubsystem<USanctuarySubsystem>();
	if (!sanctuarySystem) return;
	bActivated = sanctuarySystem->IsActivated(SanctuaryID);
	if (bActivated)
	{
		ActivateSantuary();
	}
	
	SaveMap();
}

// Called every frame
void AEKSanctuary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEKSanctuary::Interact()
{
	if (!bActivated)
	{
		ActivateSantuary();

		USanctuarySubsystem* sanctuarySystem = GetGameInstance()->GetSubsystem<USanctuarySubsystem>();
		if (!sanctuarySystem) return;
		sanctuarySystem->ActivateSanctuary(SanctuaryID);

		bActivated = true;
	}

	LoadMap();
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

void AEKSanctuary::SaveMap()
{
	// Save Enemy Transform
	TArray<AActor*> EnemyArray;
	UGameplayStatics::GetAllActorsOfClass(this, AEK_EnemyBase::StaticClass(), EnemyArray);
	for (const auto actor : EnemyArray)
	{
		AEK_EnemyBase* enemy = Cast<AEK_EnemyBase>(actor);
		if (!enemy) continue;

		if (enemy->SantuaryID == SanctuaryID)
		{
			SavedActors.Add(actor);
			SavedTransforms.Add(enemy->GetTransform());
			SavedClasses.Add(enemy->GetClass());
		}
	}
}

void AEKSanctuary::LoadMap()
{
	// Load Enemy Transform
	for (int i = 0; i < SavedActors.Num(); i++)
	{
		if (!SavedTransforms.IsValidIndex(i) || !SavedClasses.IsValidIndex(i))
		{
			continue;
		}

		const auto actor = SavedActors[i];
		if (IsValid(actor))
		{
			AEK_EnemyBase* enemy = Cast<AEK_EnemyBase>(actor);

			// Recover Start State

			// Set Transform
			enemy->StopAnimMontage();
		}
		else
		{
			AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(SavedClasses[i]);
			AEK_EnemyBase* enemy = Cast<AEK_EnemyBase>(spawnedActor);
			if (!enemy)
			{
				UE_LOG(LogTemp, Warning, TEXT("AEKSanctuary : Failed to Spawn Saved Enemy."));
			}

			// Recover Start State

			// Set Transform
			enemy->SetActorTransform(SavedTransforms[i], false, nullptr, ETeleportType::ResetPhysics);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(Handle_Transform,
		[&]() {
			for (int i = 0; i < SavedActors.Num(); i++)
			{
				if (SavedActors[i])
					SavedActors[i]->SetActorTransform(SavedTransforms[i], false, nullptr, ETeleportType::ResetPhysics);
			}
		},
		0.5, false);
}

