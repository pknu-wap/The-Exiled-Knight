// Made by Somalia Pirate


#include "EquipWeapon.h"
#include "../EKPlayer/EKPlayer.h"
#include "../EKPlayer/EKPlayerController.h"
#include "../Weapon/GreatSword.h"

void UEquipWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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
				if (EKPlayerController->bIsEquipWeapon == false)
				{
					EKPlayer->AttachWeaponToHandSocket(EKPlayer->GetCurrentWeapon());
					EKPlayerController->bIsEquipWeapon = true;
				}
				else if (EKPlayerController->bIsEquipWeapon == true)
				{
					EKPlayer->AttachWeaponToSpineSocket(EKPlayer->GetCurrentWeapon());
					EKPlayerController->bIsEquipWeapon = false;
				}
			}
		}
	}
}