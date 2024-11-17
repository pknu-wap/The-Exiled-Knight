// Made by Somalia Pirate

#include "ThunderingAttack.h"

void UThunderingAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

		SummonTundering();
		SummonTunderingTimer();
	}
}

void UThunderingAttack::SummonTundering()
{
	if (SummonTunder == 5)
	{
		EKPlayer->GetWorldTimerManager().ClearTimer(TunderSummonHandle);
		SummonTunder = 0;
		return;
	}

	SummonTunder++;

	FVector SpawnLocation = EKPlayer->GetActorLocation() + EKPlayer->GetActorForwardVector() * ThunderLocation * SummonTunder;
	FRotator SpawnRotation = EKPlayer->GetActorRotation();

	AEKPlayerProjectile* SpawnMagic = nullptr;

	if (SummonTunder == 1)
	{
		SpawnMagic = EKPlayer->GetWorld()->SpawnActor<AEKPlayerProjectile>(Thundering1, SpawnLocation, SpawnRotation);
	}
	else if (SummonTunder == 2)
	{
		SpawnMagic = EKPlayer->GetWorld()->SpawnActor<AEKPlayerProjectile>(Thundering2, SpawnLocation, SpawnRotation);
	}
	else if (SummonTunder == 3)
	{
		SpawnMagic = EKPlayer->GetWorld()->SpawnActor<AEKPlayerProjectile>(Thundering3, SpawnLocation, SpawnRotation);
	}
	else if (SummonTunder == 4)
	{
		SpawnMagic = EKPlayer->GetWorld()->SpawnActor<AEKPlayerProjectile>(Thundering3, SpawnLocation, SpawnRotation);
	}
	else if (SummonTunder == 5)
	{
		SpawnMagic = EKPlayer->GetWorld()->SpawnActor<AEKPlayerProjectile>(Thundering3, SpawnLocation, SpawnRotation);
	}
}

void UThunderingAttack::SummonTunderingTimer()
{
	EKPlayer->GetWorldTimerManager().SetTimer(TunderSummonHandle, this, &ThisClass::SummonTundering, 0.25f, true);
}