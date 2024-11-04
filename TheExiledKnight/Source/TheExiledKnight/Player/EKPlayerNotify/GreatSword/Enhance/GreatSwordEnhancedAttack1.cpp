// Made by Somalia Pirate

#include "GreatSwordEnhancedAttack1.h"
#include "../../../EKPlayer/EKPlayer.h"
#include "../../../EKPlayer/EKPlayerController.h"
#include "../../../EKPlayerGameplayTags.h"

void UGreatSwordEnhancedAttack1::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (EKPlayer = Cast<AEKPlayer>(MeshComp->GetOwner()))
	{
		EKPlayerController = Cast<AEKPlayerController>(EKPlayer->GetController());
	}

	if (EKPlayerController)
	{
		EKPlayerController->SetAttackEndTimer(3.f);
	}
}

void UGreatSwordEnhancedAttack1::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

}

void UGreatSwordEnhancedAttack1::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (EKPlayerController)
	{
		EKPlayerController->SetAttackNextAndTimer();
	}

	if (EKPlayer)
	{
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
		EKPlayer->bUseControllerRotationYaw = false;
	}
}