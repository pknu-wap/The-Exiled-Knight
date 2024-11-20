// Made by Somalia Pirate

#include "MagicRedCircle.h"

void UMagicRedCircle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

		FVector SpawnLocation = EKPlayer->GetActorLocation() + EKPlayer->GetActorUpVector() * -90.f;

		AEKPlayerProjectile* SpawnMagic = EKPlayer->GetWorld()->SpawnActor<AEKPlayerProjectile>(RedCircle, SpawnLocation, EKPlayer->GetActorRotation());

		SpawnMagic->GetCollisionComponent()->IgnoreActorWhenMoving(EKPlayer, true);
	}
}