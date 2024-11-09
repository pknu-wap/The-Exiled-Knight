// Fill out your copyright notice in the Description page of Project Settings.

#include "EKEnemyProjectileBase.h"
#include"GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include"Player/EKPlayer/EKPlayer.h"
#include"Sound/SoundBase.h"
// Sets default values
AEKEnemyProjectileBase::AEKEnemyProjectileBase()
{
#pragma region InitialSetting

	

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = CollisionBox;

	CollisionBox->OnComponentHit.AddDynamic(this, &AEKEnemyProjectileBase::OnHit);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile_Mesh"));
	ProjectileMesh->SetupAttachment(CollisionBox);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile_Component"));
	ProjectileComponent->InitialSpeed = InitialSpeed;
	ProjectileComponent->MaxSpeed = MaxSpeed;
	ProjectileComponent->ProjectileGravityScale = GravityScale; 
	ProjectileMesh->SetupAttachment(CollisionBox); 
	ProjectileComponent->bRotationFollowsVelocity = bIsRotation;
	
	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailParticle"));
	TrailParticle->SetupAttachment(RootComponent);  
	TrailParticle->bAutoActivate = true; 
#pragma endregion 
}

UBoxComponent *AEKEnemyProjectileBase::GetCollisionComponent()
{
	return CollisionBox;
}



// Called when the game starts or when spawned
void AEKEnemyProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEKEnemyProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.Location, FRotator::ZeroRotator, true);  
		AEKPlayer* HitPlayer = Cast<AEKPlayer>(OtherActor);
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, Hit.Location); 
		}
		if (HitPlayer)
		{
			UGameplayStatics::ApplyDamage(OtherActor, 10, Hit.GetActor()->GetInstigatorController(), this,DamageTypeClass );
		}
	}
	

	Destroy();
}

void AEKEnemyProjectileBase::SetHomingTarget(AActor* TargetActor)
{
	if (TargetActor&&bIsHoming)
	{
		ProjectileComponent->HomingTargetComponent = TargetActor->GetRootComponent(); 
	}
}

