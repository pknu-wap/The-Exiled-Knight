// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyWeapon/EKCrossPatternAttack.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AEKCrossPatternAttack::AEKCrossPatternAttack()
{
    SecondCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SecondCollisionBox"));
    SecondCollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    SecondCollisionBox->SetupAttachment(RootComponent);

    // 콜리전 이벤트 바인딩
    SecondCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEKCrossPatternAttack::OnOverlapBegin);
}

void AEKCrossPatternAttack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

