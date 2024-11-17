// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyWeapon/EKAttackActorBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include"Player/EKPlayer/EKPlayer.h"

// Sets default values
AEKAttackActorBase::AEKAttackActorBase()
{
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEKAttackActorBase::OnOverlapBegin);
}

void AEKAttackActorBase::SetDamage(float Amount)
{
	Damage = Amount;
}

void AEKAttackActorBase::SetInstigatorActor(AActor* Actor)
{
	InstigatorActor = Actor;
}

// Called when the game starts or when spawned
void AEKAttackActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (InstigatorActor)
	{
		HitActors.Add(InstigatorActor);
	}
}

void AEKAttackActorBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && !HitActors.Contains(OtherActor))
	{
		HitActors.Add(OtherActor);
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, nullptr);
	}
}


