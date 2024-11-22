// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheExiledKnightGameMode.h"
#include "TheExiledKnightCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheExiledKnightGameMode::ATheExiledKnightGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/EKPlayer/Blueprint/BP_Player.BP_Player_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
