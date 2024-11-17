// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spear.h"
#include "SpearTypeB.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API ASpearTypeB : public ASpear
{
	GENERATED_BODY()

public:
	ASpearTypeB();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	// Spear Animation Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> SpearSkillAnim;
};