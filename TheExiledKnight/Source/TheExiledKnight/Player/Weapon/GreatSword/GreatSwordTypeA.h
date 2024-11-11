// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GreatSword.h"
#include "GreatSwordTypeA.generated.h"

class UAnimMontage;

UCLASS()
class THEEXILEDKNIGHT_API AGreatSwordTypeA : public AGreatSword
{
	GENERATED_BODY()
	
public:	
	AGreatSwordTypeA();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void PlaySkillStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> GreatSwordSkillAnim;
};
