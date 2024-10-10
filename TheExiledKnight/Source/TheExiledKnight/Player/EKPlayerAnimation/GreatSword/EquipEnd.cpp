// Made by Somalia Pirate


#include "EquipEnd.h"
#include "../../EKPlayer/EKPlayer.h"
#include "../../Weapon/GreatSword.h"

void UEquipEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

    if (MeshComp && MeshComp->GetOwner())
    {
        AActor* OwnerActor = MeshComp->GetOwner();

        EKPlayer = Cast<AEKPlayer>(OwnerActor);

        if (EKPlayer != nullptr)
        {
            EKPlayer->AttachGreatSwordToHandSocket(Cast<AGreatSword>(EKPlayer->GetCurrentWeapon()));
        }
    }
}
