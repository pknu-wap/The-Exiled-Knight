// Made by Somalia Pirate


#include "HitEnd.h"
#include "../../EKPlayer/EKPlayer.h"
#include "../../EKPlayerGameplayTags.h"

void UHitEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Hit);
	}
}