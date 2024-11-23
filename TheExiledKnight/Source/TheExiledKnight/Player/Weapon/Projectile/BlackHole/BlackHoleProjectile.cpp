// Made by Somalia Pirate

#include "BlackHoleProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"

ABlackHoleProjectile::ABlackHoleProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent->InitialSpeed = 0.f;
	ProjectileMovementComponent->MaxSpeed = 0.f;
	ProjectileMovementComponent->Velocity = FVector(0, 0, 0);

	BaseParticle->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	CapsuleComponent->SetCapsuleHalfHeight(150.f);
	CapsuleComponent->SetCapsuleRadius(150.f);

	BlackHoleRange = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BlackHoleRange"));
	BlackHoleRange->SetupAttachment(RootComponent);
	BlackHoleRange->SetCapsuleHalfHeight(1200.f);
	BlackHoleRange->SetCapsuleRadius(1200.f);

	SetLifeSpan(5.f);

	DamageValue = 2.f;
}

void ABlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (BlackHoleEffect)
	{
		SpawnedEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BlackHoleEffect, GetActorLocation(), GetActorRotation());
	}

	DamageTimer();
}

void ABlackHoleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CapsuleLocation = BlackHoleRange->GetComponentLocation();
	FRotator CapsuleRotation = BlackHoleRange->GetComponentRotation();
	float CapsuleHalfHeight = BlackHoleRange->GetScaledCapsuleHalfHeight();
	float CapsuleRadius = BlackHoleRange->GetScaledCapsuleRadius();

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
			HitEnemy->AddMovementInput(CapsuleComponent->GetComponentLocation() - HitEnemy->GetActorLocation());
		}
	}
}

void ABlackHoleProjectile::CanDamaged()
{
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
			UGameplayStatics::ApplyDamage(HitEnemy, EKPlayer->GetPlayerStatusComponent()->GetPlayerFinalDamage() * DamageValue, EKPlayerController, EKPlayer, PlayerDamageType);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("Black Hole"));
		}
	}

	SpawnedEffect->DestroyComponent();
	Destroy();
}

void ABlackHoleProjectile::DamageTimer()
{
	GetWorldTimerManager().SetTimer(DamageHandle, this, &ThisClass::CanDamaged, DamageTime, false);
}