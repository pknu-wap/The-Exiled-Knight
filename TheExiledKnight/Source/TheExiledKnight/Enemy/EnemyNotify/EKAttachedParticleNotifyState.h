// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EKAttachedParticleNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UEKAttachedParticleNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:


    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
   
    UPROPERTY(EditAnywhere, Category = Particle, Meta = (AllowPrivteAccess = true))
    UParticleSystem* ParticleSystem;

    UPROPERTY(EditAnywhere, Category = Particle,Meta=(AllowPrivateAccess=true))
    FVector  InitialScale = FVector(1.0f, 1.0f, 1.0f);

    UPROPERTY(EditAnywhere, Category = Particle, Meta = (AllowPrivteAccess = true))
    FName SocketName; 

    UParticleSystemComponent* SpawnedParticleSystem;


};
