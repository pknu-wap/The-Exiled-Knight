// Made by Somalia Pirate

#include "MagicThunderAttack.h"

void UMagicThunderAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

		TArray<FVector> SpawnLocations = 
		{
			EKPlayer->GetActorLocation() + EKPlayer->GetActorForwardVector() * 100.f,
			EKPlayer->GetActorLocation() + EKPlayer->GetActorForwardVector() * 80.f + EKPlayer->GetActorRightVector() * 60.f,
			EKPlayer->GetActorLocation() + EKPlayer->GetActorForwardVector() * 80.f + EKPlayer->GetActorRightVector() * -60.f,
			EKPlayer->GetActorLocation() + EKPlayer->GetActorForwardVector() * 60.f + EKPlayer->GetActorRightVector() * 80.f,
			EKPlayer->GetActorLocation() + EKPlayer->GetActorForwardVector() * 60.f + EKPlayer->GetActorRightVector() * -80.f
		};

		TArray<float> Angles = { 0.0f, 10.0f, -10.0f, 20.0f, -20.0f };

		for (int i = 0; i < 5; i++)
		{
			FRotator SpawnRotation = EKPlayer->GetActorRotation();
			SpawnRotation.Yaw += Angles[i];
			AEKPlayerProjectile* SpawnMagic = EKPlayer->GetWorld()->SpawnActor<AEKPlayerProjectile>(ThunderBall, SpawnLocations[i], SpawnRotation);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Spawn Thunder"));
			SpawnMagic->GetCollisionComponent()->IgnoreActorWhenMoving(EKPlayer, true);
		}
	}
}