// Made by Somalia Pirate

#include "TeleportProjectile.h"

ATeleportProjectile::ATeleportProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent->InitialSpeed = 0.f;
	ProjectileMovementComponent->MaxSpeed = 0.f;
	ProjectileMovementComponent->Velocity = FVector(0, 0, 0);

	BaseParticle->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	SetLifeSpan(2.f);
}

void ATeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (TeleportEffect)
	{
		SpawnedTeleportEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TeleportEffect, GetActorLocation(), GetActorRotation());
	}

	if (TeleportUnderEffect)
	{
		SpawnedTeleportUnderEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TeleportUnderEffect, GetActorLocation() + GetActorUpVector() * -90, GetActorRotation());
	}

	RemoveEffectTimer();
}

void ATeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector BoxLocation = EKPlayer->GetTargetFindLockOnBox()->GetComponentLocation();
	FRotator BoxRotation = EKPlayer->GetTargetFindLockOnBox()->GetComponentRotation();
	FVector BoxExtent = EKPlayer->GetTargetFindLockOnBox()->GetScaledBoxExtent();

	TArray<FHitResult> HitResults;

	bool bIsHit = this->GetWorld()->SweepMultiByChannel(
		HitResults,
		BoxLocation,
		BoxLocation,
		BoxRotation.Quaternion(),
		ECC_Pawn,
		FCollisionShape::MakeBox(BoxExtent)
	);

	if (!bIsHit || bIsTeleport)
	{
		return;
	}

	for (auto& Hit : HitResults)
	{
		HitEnemy = Cast<AEK_EnemyBase>(Hit.GetActor());
		if (HitEnemy)
		{
			TeleportTimer();
			bIsTeleport = true;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, TEXT("Find Teleport Target"));
			break;
		}
	}
}

void ATeleportProjectile::CanTeleport()
{
	FVector TeleportLocation = HitEnemy->GetActorLocation() + HitEnemy->GetActorForwardVector() * -200;
	EKPlayer->SetActorLocation(TeleportLocation);
	EKPlayer->SetActorRotation(HitEnemy->GetActorRotation());
}

void ATeleportProjectile::TeleportTimer()
{
	GetWorldTimerManager().SetTimer(TeleportTimeHandle, this, &ThisClass::CanTeleport, TeleportTime, false);
}

void ATeleportProjectile::RemoveEffect()
{
	SpawnedTeleportEffect->DestroyComponent();
	SpawnedTeleportUnderEffect->DestroyComponent();
}

void ATeleportProjectile::RemoveEffectTimer()
{
	GetWorldTimerManager().SetTimer(RemoveEffectTimeHandle, this, &ThisClass::RemoveEffect, TeleportTime, false);
}