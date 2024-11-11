// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Staff.h"
#include "StaffTypeA.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AStaffTypeA : public AStaff
{
	GENERATED_BODY()
	
public:
	AStaffTypeA();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> StaffSkillAnim;
};