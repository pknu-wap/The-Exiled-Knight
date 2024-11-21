// Made by Somalia Pirate

#include "WaterBallProjectile.h"

AWaterBallProjectile::AWaterBallProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent->ProjectileGravityScale = 0.15f;
	ProjectileMovementComponent->InitialSpeed = 600.f;
	ProjectileMovementComponent->MaxSpeed = 600.f;

	BaseParticle->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	DamageValue = 0.5;
}

void AWaterBallProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void AWaterBallProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		AEK_EnemyBase* HitEnemy = Cast<AEK_EnemyBase>(Hit.GetActor());

		if (IgnoreEnemy.Contains(HitEnemy))
		{
			continue;
		}

		if (HitEnemy)
		{
			IgnoreEnemy.Emplace(HitEnemy);
			TSubclassOf<UEKPlayerNormalDamageType> PlayerDamageType = UEKPlayerNormalDamageType::StaticClass();
			UGameplayStatics::ApplyDamage(HitEnemy, EKPlayer->GetPlayerStatusComponent()->GetPlayerFinalDamage() * DamageValue, EKPlayerController, EKPlayer->GetCurrentWeapon(), PlayerDamageType);
			if (HitParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, HitEnemy->GetActorLocation(), HitEnemy->GetActorRotation());
			}
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Water Ball"));
		}
	}
}