// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "BlackHoleProjectile.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API ABlackHoleProjectile : public AEKPlayerProjectile
{
	GENERATED_BODY()
	
public:	
	ABlackHoleProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UNiagaraSystem* BlackHoleEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UCapsuleComponent* BlackHoleRange;

	UNiagaraComponent* SpawnedEffect;

protected:
	FTimerHandle DamageHandle;

	float DamageTime = 2.f;

	void CanDamaged();

	void DamageTimer();
};