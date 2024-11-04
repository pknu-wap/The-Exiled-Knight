// Fill out your copyright notice in the Description page of Project Settings.


#include "EKEnemyAIController.h"
#include"Perception/AIPerceptionComponent.h"
#include"Perception/AISenseConfig.h"
#include"Perception/AIPerceptionTypes.h"


AEKEnemyAIController::AEKEnemyAIController()
{
#pragma region AIPerception
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);

#pragma region Sight
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = SightRadius;
	SightConfig->LoseSightRadius = LostSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = -1.f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());
#pragma endregion
#pragma region Hearing
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->HearingRange = HearingRange;
	HearingConfig->SetMaxAge(3.f);

	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AIPerception->ConfigureSense(*HearingConfig);

#pragma endregion

	DamageSenseConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageSenseConfig"));
	AIPerception->ConfigureSense(*DamageSenseConfig);
#pragma endregion

}
#pragma region Perception

void AEKEnemyAIController::PerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* UpdatedActor : UpdatedActors)
	{
		FAIStimulus AIStimulus;
		AIStimulus = CanSenseActor(UpdatedActor, EAIPerceptionSense::SIGHT);
		if (AIStimulus.WasSuccessfullySensed())
		{
			UE_LOG(LogTemp, Warning, TEXT("Sight Sensed!"));
			HandleSensedSight(UpdatedActor);
		}
		AIStimulus = CanSenseActor(UpdatedActor, EAIPerceptionSense::HEARING);
		if(AIStimulus.WasSuccessfullySensed())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hearing Sensed!"));
			HandleSensedHearing(AIStimulus.StimulusLocation);
		}
		AIStimulus = CanSenseActor(UpdatedActor, EAIPerceptionSense::DAMAGE);
		if (AIStimulus.WasSuccessfullySensed())
		{
			UE_LOG(LogTemp, Warning, TEXT("Damgage Sensed!"));
			HandleSensedDamage(UpdatedActor); 
		}
	
	}
}

FAIStimulus AEKEnemyAIController::CanSenseActor(AActor* Actor, EAIPerceptionSense AIPerceptionSense)
{
	FActorPerceptionBlueprintInfo ActorPerceptionBlueprintInfo;
	FAIStimulus ResultStimulus;  

	AIPerception->GetActorsPerception(Actor, ActorPerceptionBlueprintInfo);  

	TSubclassOf<UAISense> QuerySenseClass;
	switch (AIPerceptionSense)
	{
	case EAIPerceptionSense::NONE:
		break;
	case EAIPerceptionSense::SIGHT:
		QuerySenseClass = UAISense_Sight::StaticClass();
		break;
	case EAIPerceptionSense::HEARING:
		QuerySenseClass = UAISense_Hearing::StaticClass();
		break;
	case EAIPerceptionSense::DAMAGE:
		QuerySenseClass = UAISense_Damage::StaticClass();
		break;
	
	default:
		break;
	}

	TSubclassOf<UAISense> LastSensedStimulusClass;

	for (const FAIStimulus& AIStimulus : ActorPerceptionBlueprintInfo.LastSensedStimuli)
	{
		LastSensedStimulusClass = UAIPerceptionSystem::GetSenseClassForStimulus(this, AIStimulus);


		if (QuerySenseClass == LastSensedStimulusClass)
		{
			ResultStimulus = AIStimulus;
			return ResultStimulus;
		}

	}
	return ResultStimulus;

}

void AEKEnemyAIController::HandleSensedSight(AActor* Actor)
{
}

void AEKEnemyAIController::HandleSensedHearing(FVector NoiseLocation)
{
}

void AEKEnemyAIController::HandleSensedDamage(AActor* Actor)
{
}


/*
bool UAIPerceptionComponent::GetActorsPerception(AActor* Actor, FActorPerceptionBlueprintInfo& Info)
{
	bool bInfoFound = false;
	if (Actor != nullptr && Actor->IsPendingKillPending() == false)
	{
		const FActorPerceptionInfo* PerceivedInfo = GetActorInfo(*Actor);
		if (PerceivedInfo)
		{
			Info = FActorPerceptionBlueprintInfo(*PerceivedInfo);
			bInfoFound = true;
		}
	}

	return bInfoFound;
}
*/
#pragma endregion





	
	



