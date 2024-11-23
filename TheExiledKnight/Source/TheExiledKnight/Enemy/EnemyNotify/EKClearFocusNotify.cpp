// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyNotify/EKClearFocusNotify.h"
#include "AIController.h"

void UEKClearFocusNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp)return;

	AActor* OwnerActor = MeshComp->GetOwner();

	if (!OwnerActor)return;
	AAIController* AIController = Cast<AAIController>(OwnerActor->GetInstigatorController());
	if (!AIController)return;
	AIController->ClearFocus(EAIFocusPriority::Gameplay);
}
