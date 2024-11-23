// Made by Somalia Pirate

#include "RedCircleProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"

ARedCircleProjectile::ARedCircleProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent->InitialSpeed = 0.f;
	ProjectileMovementComponent->MaxSpeed = 0.f;
	ProjectileMovementComponent->Velocity = FVector(0, 0, 0);

	BaseParticle->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));

	CapsuleComponent->SetCapsuleHalfHeight(700.f);
	CapsuleComponent->SetCapsuleRadius(700.f);

	SetLifeSpan(10.f);

	DamageValue = 0.1;
}

void ARedCircleProjectile::BeginPlay()
{
	Super::BeginPlay();

	DamageTimer();
}

void ARedCircleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bCanDamaged)
	{
		return;
	}

	FVector CapsuleLocation = CapsuleComponent->GetComponentLocation();
	FRotator CapsuleRotation = CapsuleComponent->GetComponentRotation();
	float CapsuleHalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
	float CapsuleRadius = CapsuleComponent->GetScaledCapsuleRadius();

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
			UGameplayStatics::ApplyDamage(HitEnemy, EKPlayer->GetPlayerStatusComponent()->GetPlayerFinalDamage() * DamageValue, EKPlayerController, EKPlayer, PlayerDamageType);
			HitEnemy->GetCharacterMovement()->MaxWalkSpeed = 100;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Red Circle"));
		}
	}

	DamageTimer();
}

void ARedCircleProjectile::CanDamaged()
{
	bCanDamaged = true;

	for (auto& Hit : HitResults)
	{
		AEK_EnemyBase* HitEnemy = Cast<AEK_EnemyBase>(Hit.GetActor());
		if (HitEnemy)
		{
			HitEnemy->GetCharacterMovement()->MaxWalkSpeed = 200;
		}
	}
}

void ARedCircleProjectile::DamageTimer()
{
	bCanDamaged = false;
	GetWorldTimerManager().SetTimer(DamageHandle, this, &ThisClass::CanDamaged, DamageTime, true);
}