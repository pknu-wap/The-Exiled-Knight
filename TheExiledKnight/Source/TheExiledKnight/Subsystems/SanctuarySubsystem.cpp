// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/SanctuarySubsystem.h"


void USanctuarySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	SanctuaryDB = LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/TheExiledKnight/Map/Sanctuary/DT_Sanctuary.DT_Sanctuary'"));
	if (SanctuaryDB)
	{
		for (FName RowName : SanctuaryDB->GetRowNames())
		{
			FSanctuaryStruct* sanctuaryInfo = SanctuaryDB->FindRow<FSanctuaryStruct>(RowName, TEXT("USanctuarySubsystem::Initialize"));
			if (sanctuaryInfo)
			{
				SanctuaryMap.Add(sanctuaryInfo->SanctuaryID, *sanctuaryInfo);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USanctuarySubsystem : Failed to get SanctuaryDB."));
	}

	ActivatedSanctuary.Add(1);
	ActivatedSanctuary.Add(2);
}

void USanctuarySubsystem::ActivateSanctuary(int SanctuaryID)
{
	ActivatedSanctuary.Add(SanctuaryID);
}

bool USanctuarySubsystem::IsActivated(int SanctuaryID)
{
	for (int i = 0; i < ActivatedSanctuary.Num(); i++)
	{
		if (ActivatedSanctuary[i] == SanctuaryID)
			return true;
	}

	return false;
}
