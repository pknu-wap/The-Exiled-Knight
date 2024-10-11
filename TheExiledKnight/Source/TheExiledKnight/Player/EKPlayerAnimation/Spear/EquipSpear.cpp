// Made by Somalia Pirate


#include "EquipSpear.h"
#include "../../EKPlayer/EKPlayer.h"
#include "../../EKPlayer/EKPlayerController.h"
#include "../../Weapon/Spear.h"

void UEquipSpear::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp && MeshComp->GetOwner())
	{
		AActor* OwnerActor = MeshComp->GetOwner();

		EKPlayer = Cast<AEKPlayer>(OwnerActor);
		if (EKPlayer)
		{
			EKPlayerController = Cast<AEKPlayerController>(EKPlayer->GetController());
			if (EKPlayerController)
			{
				if (EKPlayerController->bIsEquipSpear == false)
				{
					EKPlayer->AttachGreatSwordToHandSocket(EKPlayer->GetCurrentWeapon());
					EKPlayerController->bIsEquipSpear = true;
				}
				else if (EKPlayerController->bIsEquipSpear == true)
				{
					EKPlayer->AttachGreatSwordToEquipSocket(EKPlayer->GetCurrentWeapon());
					EKPlayerController->bIsEquipSpear = false;
				}
			}
		}
	}
}