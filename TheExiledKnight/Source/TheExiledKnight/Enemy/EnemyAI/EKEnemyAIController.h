
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "EKEnemyAIController.generated.h"

UENUM(BlueprintType)
enum class EAIPerceptionSense : uint8 // SENSE ENUM 
{
	NONE UMETA(DisplayName = "None"),
	SIGHT UMETA(DisplayName = "Sight"),
	HEARING UMETA(DisplayName = "Hearing"),
	DAMAGE UMETA(DisplayName = "Damage")
};

UCLASS()
class THEEXILEDKNIGHT_API AEKEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEKEnemyAIController();

	// AIPerception Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Perception")
	UAIPerceptionComponent* AIPerception;

	


private:
	// AIPerception Sense Configurations
	UPROPERTY(VisibleAnywhere, Category = "AI|Perception")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, Category = "AI|Perception")
	UAISenseConfig_Hearing* HearingConfig;

	UPROPERTY(VisibleAnywhere, Category = "AI|Perception")
	UAISenseConfig_Damage* DamageSenseConfig;

	// Perception ranges
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception", meta = (AllowPrivateAccess = "true"))
	float SightRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception", meta = (AllowPrivateAccess = "true"))
	float LostSightRadius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception", meta = (AllowPrivateAccess = "true"))
	float HearingRange = 3000.0f;

	TObjectPtr<class EK_EnemyBase>EKEnemy;
};
