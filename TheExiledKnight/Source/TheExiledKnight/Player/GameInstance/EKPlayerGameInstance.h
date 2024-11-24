// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Player/Data/EKPlayerLevel.h"
#include "Player/Data/EKPlayerStatus.h"
#include "Player/Data/EKPlayerMagic.h"
#include "Player/Data/EKPlayerDomainExpansion.h"
#include "Engine/DataTable.h"
#include "EKPlayerGameInstance.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API UEKPlayerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UEKPlayerGameInstance();

protected:
	virtual void Init();

public:
	FEKPlayerLevel* GetEKPlayerLevelData(int32 Level);
	FEKPlayerStatus* GetEKPlayerStatusData(int32 Level);
	FEKPlayerMagic* GetEKPlayerMagicData(int32 Level);
	FEKPlayerDomainExpansion* GetEKPlayerDomainExpansion(int32 Level);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* EKPlayerLevelData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* EKPlayerStatusData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* EKPlayerMagicData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* EKPlayerDomainExpansionData;
};