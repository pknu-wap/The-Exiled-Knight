// Fill out your copyright notice in the Description page of Project Settings.


#include "EKEnemyRootMotionNotifyState.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include"Enemy/EK_EnemyBase.h"

void UEKEnemyRootMotionNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration); 
	Owner = MeshComp->GetOwner(); 
	ACharacter* OwnerCharacter = Cast<ACharacter>(Owner); 
	AEK_EnemyBase* OwnerCheck = Cast<AEK_EnemyBase>(Owner);
	OwnerCheck->SetAttackHitCheck(false);
	if (!OwnerCharacter)return;

	  
	if(OwnerCharacter->GetCharacterMovement())
	{
		UCharacterMovementComponent* MovementComponent = OwnerCharacter->GetCharacterMovement(); 
		MovementComponent->bAllowPhysicsRotationDuringAnimRootMotion = true;
		
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
		
		UE_LOG(LogTemp, Warning, TEXT("Root motion rotation is not allowed for %s"), *OwnerCharacter->GetName());
	}
}
