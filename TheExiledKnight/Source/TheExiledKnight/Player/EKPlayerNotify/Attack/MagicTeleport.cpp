// Made by Somalia Pirate

#include "MagicTeleport.h"

void UMagicTeleport::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

		AEKPlayerProjectile* SpawnMagic = EKPlayer->GetWorld()->SpawnActor<AEKPlayerProjectile>(TeleportEffect, EKPlayer->GetActorLocation(), EKPlayer->GetActorRotation());
	}
}