// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EKEnemyRootMotionNotifyState.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h" 

void UEKEnemyRootMotionNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration); 
	Owner = MeshComp->GetOwner(); 
	ACharacter* OwnerCharacter = Cast<ACharacter>(Owner); 
	if (!OwnerCharacter)return;

	  
	if(OwnerCharacter->GetCharacterMovement())
	{
		UCharacterMovementComponent* MovementComponent = OwnerCharacter->GetCharacterMovement(); 
		MovementComponent->bAllowPhysicsRotationDuringAnimRootMotion = true;
		MovementComponent->bOrientRotationToMovement = false;
		UE_LOG(LogTemp, Warning, TEXT("Root motion rotation allowed for %s"), *OwnerCharacter->GetName());
	}
}

void UEKEnemyRootMotionNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Owner = MeshComp->GetOwner();
	ACharacter* OwnerCharacter = Cast<ACharacter>(Owner);
	if (!OwnerCharacter)return;
	if (OwnerCharacter->GetCharacterMovement())
	{
		UCharacterMovementComponent* MovementComponent = OwnerCharacter->GetCharacterMovement();
		MovementComponent->bAllowPhysicsRotationDuringAnimRootMotion = false;
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Root motion rotation is not allowed for %s"), *OwnerCharacter->GetName());
	}
}
