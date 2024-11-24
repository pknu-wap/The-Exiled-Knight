// Made by Somalia Pirate

#include "DomainExpansionBase.h"

ADomainExpansionBase::ADomainExpansionBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
}

void ADomainExpansionBase::BeginPlay()
{
	Super::BeginPlay();

	EKPlayer = Cast<AEKPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (EKPlayer)
	{
		EKPlayerController = Cast<AEKPlayerController>(EKPlayer->GetController());
	}

	if (DomainExpansionEffect)
	{
		SpawnedDomainExpansion = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DomainExpansionEffect, EKPlayer->GetActorLocation(), EKPlayer->GetActorRotation());
	}

	EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_DomainExpansion);

	DomainExpansionTimer();

	RemoveEffectTimer();
}

void ADomainExpansionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnedDomainExpansion->SetWorldScale3D(FVector(DomainSize, DomainSize, DomainSize));
	SphereComponent->SetWorldScale3D(FVector(DomainSize, DomainSize, DomainSize));
}

void ADomainExpansionBase::DomainExpansion()
{
	if (DomainSize >= DomainMaxSize)
	{
		return;
	}

	DomainSize += 0.04f;
}

void ADomainExpansionBase::DomainExpansionTimer()
{
	GetWorldTimerManager().SetTimer(DomainExpansionTimeHandle, this, &ThisClass::DomainExpansion, DomainExpansionTime, true);
}

void ADomainExpansionBase::RemoveEffect()
{
	EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_DomainExpansion);
	SpawnedDomainExpansion->DestroyComponent();
}

void ADomainExpansionBase::RemoveEffectTimer()
{
	GetWorldTimerManager().SetTimer(RemoveEffectTimeHandle, this, &ThisClass::RemoveEffect, DomainDuration, false);
}