// Made by Somalia Pirate


#include "UseItem.h"
#include "../../EKPlayer/EKPlayer.h"
#include "../../EKPlayer/EKPlayerController.h"
#include "../../EKPlayerGameplayTags.h"

void UUseItem::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp && MeshComp->GetOwner())
	{
		AActor* OwnerActor = MeshComp->GetOwner();

		EKPlayer = Cast<AEKPlayer>(OwnerActor);
		if (!EKPlayer)
		{
			return;
		}

		EKPlayerController = Cast<AEKPlayerController>(EKPlayer->GetController());

		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_UseItem);
	}
}