// Made by Somalia Pirate

#include "EKPlayerGameInstance.h"

UEKPlayerGameInstance::UEKPlayerGameInstance()
{
	ConstructorHelpers::FObjectFinder<UDataTable> EKPlayerLevelDataFinder(TEXT("/Game/TheExiledKnight/Player/Data/EKPlayerLevel"));
	if (EKPlayerLevelDataFinder.Succeeded())
	{
		EKPlayerLevelData = EKPlayerLevelDataFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> EKPlayerStatusDataFinder(TEXT("/Game/TheExiledKnight/Player/Data/EKPlayerStatusData"));
	if (EKPlayerStatusDataFinder.Succeeded())
	{
		EKPlayerStatusData = EKPlayerStatusDataFinder.Object;
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