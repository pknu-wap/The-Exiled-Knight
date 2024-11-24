// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EKPotion_Base.h"

AEKPotion_Base::AEKPotion_Base()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MontageFinder(TEXT("/Script/Engine.AnimMontage'/Game/TheExiledKnight/Player/Animation/Common/UseItem/EKPlayer_UsePotion_Montage.EKPlayer_UsePotion_Montage'"));

	if (MontageFinder.Succeeded())
		ItemUseAnimMontage = MontageFinder.Object;
}

void AEKPotion_Base::BeginPlay()
{
	Super::BeginPlay();

}

void AEKPotion_Base::UseItem(UWorld* WorldContext, int level)
{
	Super::UseItem(WorldContext, level);

	// Heal Health, Mana, etc...

	AEKPlayer* player = Cast<AEKPlayer>(UGameplayStatics::GetPlayerCharacter(WorldContext, 0));

	if (player != nullptr && ItemUseAnimMontage != nullptr)
	{
		player->PlayAnimMontage(ItemUseAnimMontage);
	}
}
