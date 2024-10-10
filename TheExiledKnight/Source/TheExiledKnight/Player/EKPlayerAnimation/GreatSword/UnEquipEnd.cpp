// Made by Somalia Pirate


#include "UnEquipEnd.h"
#include "../../EKPlayer/EKPlayer.h"
#include "../../Weapon/GreatSword.h"

void UUnEquipEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

    if (MeshComp && MeshComp->GetOwner())
    {
        AActor* OwnerActor = MeshComp->GetOwner();

        EKPlayer = Cast<AEKPlayer>(OwnerActor);

        if (EKPlayer != nullptr)
        {
            EKPlayer->AttachGreatSwordToEquipSocket(Cast<AGreatSword>(EKPlayer->GetCurrentWeapon()));
        }
    }
}
