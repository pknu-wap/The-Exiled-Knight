// Made by Somalia Pirate

#include "HealCircleProjectile.h"

AHealCircleProjectile::AHealCircleProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent->InitialSpeed = 0.f;
	ProjectileMovementComponent->MaxSpeed = 0.f;
	ProjectileMovementComponent->Velocity = FVector(0, 0, 0);

	BaseParticle->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));

	CapsuleComponent->SetCapsuleHalfHeight(300.f);
	CapsuleComponent->SetCapsuleRadius(300.f);

	SetLifeSpan(10.f);
}

void AHealCircleProjectile::BeginPlay()
{
	Super::BeginPlay();

	HealTimer();
}

void AHealCircleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bCanHeal)
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
		AEKPlayer* HitPlayer = Cast<AEKPlayer>(Hit.GetActor());
		if (HitPlayer)
		{
			HitPlayer->GetPlayerStatusComponent()->SetHp(50);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Heal Circle"));
			break;
		}
	}

	HealTimer();
}

void AHealCircleProjectile::CanHeal()
{
	bCanHeal = true;
}

void AHealCircleProjectile::HealTimer()
{
	bCanHeal = false;
	GetWorldTimerManager().SetTimer(HealHandle, this, &ThisClass::CanHeal, HealTime, true);
}