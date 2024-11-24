// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EKManaPotion.h"
#include "Player/EKPlayer/EKPlayerStatusComponent.h"
#include "Subsystems/InventorySubsystem.h"

AEKManaPotion::AEKManaPotion()
{
}

void AEKManaPotion::BeginPlay()
{
	Super::BeginPlay();
}

void AEKManaPotion::UseItem(UWorld* WorldContext, int level)
{
	Super::UseItem(WorldContext, level);

	AEKPlayer* player = Cast<AEKPlayer>(UGameplayStatics::GetPlayerCharacter(WorldContext, 0));

	if (player != nullptr)
	{
		int32 HealAmount;
		HealAmount = 10 * WorldContext->GetGameInstance<UInventorySubsystem>()->GetLevelRateInfo(level)->PotionHealRate;
		player->GetPlayerStatusComponent()->SetMp(HealAmount);
	}
}
