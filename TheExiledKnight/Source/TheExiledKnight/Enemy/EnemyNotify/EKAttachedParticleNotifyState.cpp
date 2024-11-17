// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyNotify/EKAttachedParticleNotifyState.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
void UEKAttachedParticleNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    if (ParticleSystem && MeshComp)
    {
        SpawnedParticleSystem = UGameplayStatics::SpawnEmitterAttached(
            ParticleSystem,
            MeshComp,
            SocketName,
            FVector::ZeroVector, 
            FRotator::ZeroRotator, 
            EAttachLocation::SnapToTarget
        );
    }
    if (SpawnedParticleSystem)
    {
        SpawnedParticleSystem->SetWorldScale3D(InitialScale);
    }
}

void UEKAttachedParticleNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (SpawnedParticleSystem)
    {
        SpawnedParticleSystem->DestroyComponent();
        SpawnedParticleSystem = nullptr;
    }
}
