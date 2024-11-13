// Made by Somalia Pirate


#include "MagicBaseAttack.h"

void UMagicBaseAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

		FVector SpawnLocation = EKPlayer->GetActorLocation() + EKPlayer->GetActorForwardVector() * 100.f;

		AEKPlayerProjectile* SpawnFireBall = EKPlayer->GetWorld()->SpawnActor<AEKPlayerProjectile>(FireBall, SpawnLocation, EKPlayer->GetActorRotation());

		SpawnFireBall->GetCollisionComponent()->IgnoreActorWhenMoving(EKPlayer, true);
	}
}