// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "TeleportProjectile.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API ATeleportProjectile : public AEKPlayerProjectile
{
	GENERATED_BODY()
	
public:	
	ATeleportProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UNiagaraSystem* TeleportEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UNiagaraComponent* SpawnedTeleportEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UNiagaraSystem* TeleportUnderEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UNiagaraComponent* SpawnedTeleportUnderEffect;

protected:
	AEK_EnemyBase* HitEnemy;

	FTimerHandle TeleportTimeHandle;
	FTimerHandle RemoveEffectTimeHandle;

	float TeleportTime = 0.66f;

	bool bIsTeleport = false;

	void CanTeleport();

	void TeleportTimer();

	void RemoveEffect();

	void RemoveEffectTimer();
};