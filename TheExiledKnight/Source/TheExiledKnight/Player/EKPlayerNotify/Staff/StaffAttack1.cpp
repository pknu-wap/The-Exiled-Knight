// Made by Somalia Pirate

#include "StaffAttack1.h"
#include "../../EKPlayer/EKPlayer.h"
#include "../../EKPlayer/EKPlayerController.h"

void UStaffAttack1::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (EKPlayer = Cast<AEKPlayer>(MeshComp->GetOwner()))
	{
		EKPlayerController = Cast<AEKPlayerController>(EKPlayer->GetController());
	}

	if (EKPlayerController)
	{
		EKPlayerController->SetAttackEndTimer(2.33f);
	}
}

void UStaffAttack1::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

}

void UStaffAttack1::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (EKPlayerController)
	{
		EKPlayerController->SetAttackNextAndTimer();
	}
}