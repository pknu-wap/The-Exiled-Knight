#include "EKEnemyProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/EKPlayer/EKPlayer.h"
#include "Sound/SoundBase.h"

// Sets default values
AEKEnemyProjectileBase::AEKEnemyProjectileBase()
{
#pragma region InitialSetting


    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    RootComponent = CollisionBox;


    CollisionBox->OnComponentHit.AddDynamic(this, &AEKEnemyProjectileBase::OnHit);


    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile_Mesh"));
    ProjectileMesh->SetupAttachment(RootComponent);


    ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile_Component"));
    ProjectileComponent->bRotationFollowsVelocity = true;
    ProjectileComponent->bShouldBounce = false;


    ProjectileMesh->SetupAttachment(CollisionBox);


    TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailParticle"));
    TrailParticle->SetupAttachment(ProjectileMesh);
    TrailParticle->bAutoActivate = true;

#pragma endregion
}

UBoxComponent* AEKEnemyProjectileBase::GetCollisionComponent()
{
    return CollisionBox;
}


void AEKEnemyProjectileBase::BeginPlay()
{
    Super::BeginPlay();

    if (ProjectileComponent)
    {
        ProjectileComponent->InitialSpeed = InitialSpeed;
        ProjectileComponent->MaxSpeed = MaxSpeed;
        ProjectileComponent->bRotationFollowsVelocity = bIsRotation;
    }


    SetLifeSpan(10.0f);
}

// 충돌 처리 함수 - 개선된 버전
void AEKEnemyProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!OtherActor || OtherActor == this)
    {
        return;
    }


    HandleImpactEffects(Hit.Location);


    AEKPlayer* HitPlayer = Cast<AEKPlayer>(OtherActor);
    if (HitPlayer)
    {
        UGameplayStatics::ApplyDamage(HitPlayer, 30.0f, Hit.GetActor()->GetInstigatorController(), Owner, DamageTypeClass);
    }

    Destroy();
}


void AEKEnemyProjectileBase::HandleImpactEffects(const FVector& ImpactLocation)
{

    if (HitEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, ImpactLocation, FRotator::ZeroRotator, true);
    }


    if (HitSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, HitSound, ImpactLocation);
    }
}



void AEKEnemyProjectileBase::SetHomingTarget(AActor* TargetActor)
{
    if (TargetActor && bIsHoming)
    {
        if (ProjectileComponent)
        {
            ProjectileComponent->HomingTargetComponent = TargetActor->GetRootComponent();
        }
    }
}