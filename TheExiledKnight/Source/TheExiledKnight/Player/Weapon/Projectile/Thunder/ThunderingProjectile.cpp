// Made by Somalia Pirate

#include "ThunderingProjectile.h"

AThunderingProjectile::AThunderingProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent->InitialSpeed = 0.f;
	ProjectileMovementComponent->MaxSpeed = 0.f;
	ProjectileMovementComponent->Velocity = FVector(0, 0, 0);

	BaseParticle->SetRelativeLocation(FVector(0, 0, -90));

	CapsuleComponent->SetCapsuleHalfHeight(200.f);

	SetLifeSpan(1.f);

	DamageValue = 0.5;
}

void AThunderingProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AThunderingProjectile::Tick(float DeltaTime)
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
			TSubclassOf<UEKPlayerStrongDamageType> PlayerDamageType = UEKPlayerStrongDamageType::StaticClass();
			if (HitEnemy)
			{
				UGameplayStatics::ApplyDamage(HitEnemy, EKPlayer->GetPlayerStatusComponent()->GetPlayerFinalDamage() * DamageValue, EKPlayerController, EKPlayer, PlayerDamageType);
				if (HitParticle)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, HitEnemy->GetActorLocation(), HitEnemy->GetActorRotation());
				}
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Thundering"));
				Destroy();
				return;
			}
		}
	}
}