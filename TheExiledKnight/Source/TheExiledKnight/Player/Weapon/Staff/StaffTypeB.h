// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Staff.h"
#include "StaffTypeB.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AStaffTypeB : public AStaff
{
	GENERATED_BODY()

public:
	AStaffTypeB();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void PlaySkillStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> StaffSkillAnim;
};