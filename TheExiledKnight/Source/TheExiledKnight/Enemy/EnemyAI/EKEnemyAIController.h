// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include"Perception/AIPerceptionComponent.h"
#include"Perception/AIPerceptionTypes.h"
#include "Enemy/EKEnemyGamePlayTags.h"
#include "EKEnemyAIController.generated.h"
/**
 * 
 */
UENUM()
enum EAIPerceptionSense //SENSE ENUM 
{
	NONE,
	SIGHT,
	HEARING,
	DAMAGE
};

UCLASS()
class THEEXILEDKNIGHT_API AEKEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEKEnemyAIController();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAIPerceptionComponent* AIPerception;

	UFUNCTION()
	void PerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	FAIStimulus CanSenseActor(AActor* Actor, EAIPerceptionSense AIPercetptionSense);
	void HandleSensedSight(AActor*Actor);
	void HandleSensedHearing(FVector NoiseLocation);
	bool GetPerceptionInfo(AActor* Actor, FActorPerceptionBlueprintInfo& OutInfo) const;
		
private:
#pragma region AIPerception
	class UAISenseConfig_Sight* SightConfig;
	class UAISenseConfig_Hearing* HearingConfig;
	class UAISenseConfig_Damage* DamageSenseConfig;
	UPROPERTY(BlueprintReadWrite, Category = Perception, meta = (AllowPrivateAccess = "true"));
	float  SightRadius;
	UPROPERTY(BlueprintReadWrite, Category = Perception, meta = (AllowPrivateAccess = "true"));
	float LostSightRadius;
	UPROPERTY(BlueprintReadWrite, Category = Perception, meta = (AllowPrivateAccess = "true"));
	float HearingRange;

#pragma endregion

};
