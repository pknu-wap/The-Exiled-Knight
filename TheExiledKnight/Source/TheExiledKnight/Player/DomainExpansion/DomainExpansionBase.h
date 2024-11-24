// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Player/EKPlayer/EKPlayer.h"
#include "Player/EKPlayer/EKPlayerController.h"
#include "Player/EKPlayer/EKPlayerStatusComponent.h"
#include "Enemy/EK_EnemyBase.h"
#include "Player/Weapon/DamageType/EKPlayerDamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Player/EKPlayerGameplayTags.h"
#include "Components/SphereComponent.h"
#include "DomainExpansionBase.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API ADomainExpansionBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ADomainExpansionBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	AEKPlayer* EKPlayer;

	AEKPlayerController* EKPlayerController;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UNiagaraSystem* DomainExpansionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UNiagaraComponent* SpawnedDomainExpansion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	USphereComponent* SphereComponent;

protected:
	FTimerHandle DomainExpansionTimeHandle;
	FTimerHandle RemoveEffectTimeHandle;

	float DomainSize = 0.1f;
	float DomainMaxSize = 10.f;
	float DomainExpansionTime = 0.01f;
	float DomainDuration = 30.f;

	void DomainExpansion();
	void DomainExpansionTimer();

	void RemoveEffect();
	void RemoveEffectTimer();
};