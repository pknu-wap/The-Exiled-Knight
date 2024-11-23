// Made by Somalia Pirate

#include "MagicRazerAttack.h"

void UMagicRazerAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

		FVector SpawnLocation = EKPlayer->GetActorLocation() + EKPlayer->GetActorForwardVector() * 100.f + EKPlayer->GetActorUpVector() * 50.f;

		AEKPlayerProjectile* SpawnMagic = EKPlayer->GetWorld()->SpawnActor<AEKPlayerProjectile>(RazerPro, SpawnLocation, EKPlayer->GetActorRotation());

		SpawnMagic->GetCollisionComponent()->IgnoreActorWhenMoving(EKPlayer, true);
	}
}