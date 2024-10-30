// Made by Somalia Pirate

#include "Dodge.h"
#include "../EKPlayer/EKPlayer.h"
#include "../EKPlayer/EKPlayerController.h"
#include "../EKPlayerGameplayTags.h"

void UDodge::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (EKPlayer = Cast<AEKPlayer>(MeshComp->GetOwner()))
	{
		EKPlayerController = Cast<AEKPlayerController>(EKPlayer->GetController());
	}
}

void UDodge::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

}

void UDodge::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (EKPlayer)
	{
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Dodge);
	}
}