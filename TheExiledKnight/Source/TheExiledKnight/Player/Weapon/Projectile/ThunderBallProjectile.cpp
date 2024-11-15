// Made by Somalia Pirate

#include "ThunderBallProjectile.h"

AThunderBallProjectile::AThunderBallProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	ProjectileMovementComponent->InitialSpeed = 600.f;
	ProjectileMovementComponent->MaxSpeed = 600.f;

	SetLifeSpan(0.8f);

	DamageValue = 0.3;
}

void AThunderBallProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AThunderBallProjectile::Tick(float DeltaTime)
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
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			AEK_EnemyBase* HitEnemy = Cast<AEK_EnemyBase>(HitActor);
			TSubclassOf<UEKPlayerDamageType> PlayerDamageType = UEKPlayerDamageType::StaticClass();
			if (HitEnemy)
			{
				UGameplayStatics::ApplyDamage(HitEnemy, EKPlayer->GetPlayerStatusComponent()->GetPlayerFinalDamage() * DamageValue, EKPlayerController, EKPlayer->GetCurrentWeapon(), PlayerDamageType);
				if (HitParticle)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, HitEnemy->GetActorLocation(), HitEnemy->GetActorRotation());
				}
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Thunder Ball"));
				Destroy();
				return;
			}
		}
	}
}