// Made by Somalia Pirate

#include "FireBallProjectile.h"

AFireBallProjectile::AFireBallProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent->ProjectileGravityScale = 0.05f;

	DamageValue = 0.5;
}

void AFireBallProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFireBallProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsHitOnce)
	{
		return;
	}

	FVector CapsuleLocation = CapsuleComponent->GetComponentLocation();
	FRotator CapsuleRotation = CapsuleComponent->GetComponentRotation();
	float CapsuleHalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
	float CapsuleRadius = CapsuleComponent->GetScaledCapsuleRadius();

	TArray<FHitResult> HitResults;

	bool bIsHit = this->GetWorld()->SweepMultiByChannel(
		HitResults,
		CapsuleLocation,
		CapsuleLocation,
		CapsuleRotation.Quaternion(),
		ECC_Pawn,
		FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight)
	);

	if (!bIsHit)
	{
		return;
	}

	for (auto& Hit : HitResults)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			AEK_EnemyBase* HitEnemy = Cast<AEK_EnemyBase>(HitActor);
			TSubclassOf<UEKPlayerDamageType> PlayerDamageType = UEKPlayerDamageType::StaticClass();
			if (HitEnemy)
			{
				UGameplayStatics::ApplyDamage(HitEnemy, EKPlayer->GetPlayerStatusComponent()->GetPlayerFinalDamage() * DamageValue, EKPlayerController, EKPlayer->GetCurrentWeapon(), PlayerDamageType);
				bIsHitOnce = true;
				if (HitParticle)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), GetActorRotation());
				}
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, TEXT("Fire Ball"));
				Destroy();
				return;
			}
		}
	}
}