// Made by Somalia Pirate


#include "AttackEnd.h"
#include "../../EKPlayer/EKPlayer.h"

void UAttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

    /*if (MeshComp && MeshComp->GetOwner())
    {
        AActor* OwnerActor = MeshComp->GetOwner();

        EKPlayer = Cast<AEKPlayer>(OwnerActor);
        if (EKPlayer != nullptr)
        {
            EKPlayer->SetPlayerCurrentState(EEKPlayerBehaviorState::Idle);
        }
    }*/
}