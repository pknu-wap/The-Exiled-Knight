// Made by Somalia Pirate

#include "RazerProjectile.h"

ARazerProjectile::ARazerProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent->InitialSpeed = 0.f;
	ProjectileMovementComponent->MaxSpeed = 0.f;
	ProjectileMovementComponent->Velocity = FVector(0, 0, 0);

	StaticMeshComponent->SetRelativeRotation(FRotator(0, 180.f, 0));

	BaseParticle->SetRelativeRotation(FRotator(90.f, 0, 0));
	BaseParticle->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));

	CapsuleComponent->SetCapsuleHalfHeight(1000.f);
	CapsuleComponent->SetCapsuleRadius(15.f);
	CapsuleComponent->SetRelativeRotation(FRotator(90.f, 0, 0));
	CapsuleComponent->SetRelativeLocation(FVector(-1010.f, 0, 0));

	SetLifeSpan(2.f);

	DamageValue = 0.05;
}

void ARazerProjectile::BeginPlay()
{
	Super::BeginPlay();

	EKPlayerController->RemoveAttackTagTimer(3.6f);
}

void ARazerProjectile::Tick(float DeltaTime)
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
			TSubclassOf<UEKPlayerDamageType> PlayerDamageType = UEKPlayerDamageType::StaticClass();
			UGameplayStatics::ApplyDamage(HitEnemy, EKPlayer->GetPlayerStatusComponent()->GetPlayerFinalDamage() * DamageValue, EKPlayerController, EKPlayer->GetCurrentWeapon(), PlayerDamageType);
			if (HitParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, HitEnemy->GetActorLocation(), HitEnemy->GetActorRotation());
			}
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Magenta, TEXT("Razer"));
		}
	}
}