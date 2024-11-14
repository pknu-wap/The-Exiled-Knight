// Made by Somalia Pirate

#include "FireStormProjectile.h"

AFireStormProjectile::AFireStormProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	StormMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StormMeshComponent"));
	StormMeshComponent->SetupAttachment(RootComponent);
	StormMeshComponent->SetRelativeScale3D(FVector(12.f, 12.f, 12.f));
	StormMeshComponent->SetRelativeLocation(FVector(0, 0, -70));

	CapsuleComponent->SetCapsuleHalfHeight(400.f);
	CapsuleComponent->SetCapsuleRadius(150.f);
	CapsuleComponent->SetRelativeLocation(FVector(0, 0, 0));

	ProjectileMovementComponent->InitialSpeed = 130.f;
	ProjectileMovementComponent->MaxSpeed = 130.f;

	BaseParticle->SetRelativeLocation(FVector(0, 0, -80));

	SetLifeSpan(12.f);

	DamageValue = 0.1;
}

void AFireStormProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void AFireStormProjectile::Tick(float DeltaTime)
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
					HitEnemy->Jump();
				}
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, TEXT("Fire Storm"));
			}
		}
	}
}