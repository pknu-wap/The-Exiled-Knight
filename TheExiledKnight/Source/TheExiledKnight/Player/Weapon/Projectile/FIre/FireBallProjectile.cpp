// Made by Somalia Pirate

#include "FireBallProjectile.h"

AFireBallProjectile::AFireBallProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent->ProjectileGravityScale = 0.05f;

	BaseParticle->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));

	DamageValue = 0.5;
}

void AFireBallProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void AFireBallProjectile::Tick(float DeltaTime)
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
		if (HitEnemy)
		{
			TSubclassOf<UEKPlayerNormalDamageType> PlayerDamageType = UEKPlayerNormalDamageType::StaticClass();
			UGameplayStatics::ApplyDamage(HitEnemy, EKPlayer->GetPlayerStatusComponent()->GetPlayerFinalDamage() * DamageValue, EKPlayerController, EKPlayer->GetCurrentWeapon(), PlayerDamageType);
			if (HitParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, HitEnemy->GetActorLocation(), HitEnemy->GetActorRotation());
			}
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fire Ball"));
			Destroy();
			return;
		}
	}
}