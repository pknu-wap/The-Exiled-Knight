// Made by Somalia Pirate

#include "StaffAttack4.h"
#include "../../EKPlayer/EKPlayer.h"
#include "../../EKPlayer/EKPlayerController.h"

void UStaffAttack4::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (EKPlayer = Cast<AEKPlayer>(MeshComp->GetOwner()))
	{
		EKPlayerController = Cast<AEKPlayerController>(EKPlayer->GetController());
	}

	if (EKPlayerController)
	{
		EKPlayerController->SetAttackEndTimer(2.67f);
	}
}

void UStaffAttack4::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

}

void UStaffAttack4::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (EKPlayerController)
	{
		EKPlayerController->SetAttackNextAndTimer();
	}
}