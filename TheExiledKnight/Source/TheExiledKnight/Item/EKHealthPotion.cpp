// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EKHealthPotion.h"
#include "Player/EKPlayer/EKPlayerStatusComponent.h"
#include "Subsystems/InventorySubsystem.h"

AEKHealthPotion::AEKHealthPotion()
{
}

void AEKHealthPotion::BeginPlay()
{
	Super::BeginPlay();
}

void AEKHealthPotion::UseItem(UWorld* WorldContext, int level)
{
	Super::UseItem(WorldContext, level);

	AEKPlayer* player = Cast<AEKPlayer>(UGameplayStatics::GetPlayerCharacter(WorldContext, 0));

	if (player != nullptr)
	{
		int32 HealAmount;
		HealAmount = 10 * WorldContext->GetGameInstance<UInventorySubsystem>()->GetLevelRateInfo(level)->PotionHealRate;
		player->GetPlayerStatusComponent()->SetHp(HealAmount);
	}
}
