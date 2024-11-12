// Made by Somalia Pirate

#include "EKPlayerProjectile.h"

AEKPlayerProjectile::AEKPlayerProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	StaticMeshComponent->SetStaticMesh(StaticMesh);
	StaticMeshComponent->SetCollisionProfileName(FName("NoCollision"));
	RootComponent = StaticMeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 1200.f;
	ProjectileMovementComponent->MaxSpeed = 1200.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetCollisionProfileName(FName("OverlapOnlyPawn"));
	CapsuleComponent->SetCapsuleHalfHeight(60.f);
	CapsuleComponent->SetCapsuleRadius(60.f);

	BaseParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BaseParticle"));
	BaseParticle->SetupAttachment(RootComponent);

	SetLifeSpan(5.f);
}

void AEKPlayerProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	EKPlayer = Cast<AEKPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (EKPlayer)
	{
		EKPlayerController = Cast<AEKPlayerController>(EKPlayer->GetController());
	}
}

void AEKPlayerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsHitOnce)
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
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			AEK_EnemyBase* HitEnemy = Cast<AEK_EnemyBase>(HitActor);
			TSubclassOf<UEKPlayerDamageType> PlayerDamageType = UEKPlayerDamageType::StaticClass();
			if (HitEnemy)
			{
				UGameplayStatics::ApplyDamage(HitEnemy, EKPlayer->GetPlayerStatusComponent()->GetPlayerFinalDamage(), EKPlayerController, EKPlayer->GetCurrentWeapon(), PlayerDamageType);
				bIsHitOnce = true;
				if (HitParticle)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), GetActorRotation());
				}
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, TEXT("Magic"));
				break;
			}
		}
	}

	Destroy();
}