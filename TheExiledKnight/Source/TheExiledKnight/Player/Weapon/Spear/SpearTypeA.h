// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spear.h"
#include "SpearTypeA.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API ASpearTypeA : public ASpear
{
	GENERATED_BODY()
	
public:	
	ASpearTypeA();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void PlaySkillStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController) override;

protected:
	// Spear Animation Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> SpearSkillAnim;
};