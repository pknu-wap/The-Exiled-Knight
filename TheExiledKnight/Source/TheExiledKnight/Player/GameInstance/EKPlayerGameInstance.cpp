// Made by Somalia Pirate

#include "EKPlayerGameInstance.h"

UEKPlayerGameInstance::UEKPlayerGameInstance()
{
	ConstructorHelpers::FObjectFinder<UDataTable> EKPlayerLevelDataFinder(TEXT("/Game/TheExiledKnight/Player/Data/EKPlayerLevel"));
	if (EKPlayerLevelDataFinder.Succeeded())
	{
		EKPlayerLevelData = EKPlayerLevelDataFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> EKPlayerStatusDataFinder(TEXT("/Game/TheExiledKnight/Player/Data/EKPlayerStatus"));
	if (EKPlayerStatusDataFinder.Succeeded())
	{
		EKPlayerStatusData = EKPlayerStatusDataFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> EKPlayerMagicDataFinder(TEXT("/Game/TheExiledKnight/Player/Data/EKPlayerMagic"));
	if (EKPlayerMagicDataFinder.Succeeded())
	{
		EKPlayerMagicData = EKPlayerMagicDataFinder.Object;
	}
}

void UEKPlayerGameInstance::Init()
{
	Super::Init();

}

FEKPlayerLevel* UEKPlayerGameInstance::GetEKPlayerLevelData(int32 Level)
{
	return EKPlayerLevelData->FindRow<FEKPlayerLevel>(*FString::FromInt(Level),TEXT(""));
}

FEKPlayerStatus* UEKPlayerGameInstance::GetEKPlayerStatusData(int32 Level)
{
	return EKPlayerStatusData->FindRow<FEKPlayerStatus>(*FString::FromInt(Level), TEXT(""));
}

FEKPlayerMagic* UEKPlayerGameInstance::GetEKPlayerMagicData(int32 Level)
{
	return EKPlayerMagicData->FindRow<FEKPlayerMagic>(*FString::FromInt(Level), TEXT(""));
}