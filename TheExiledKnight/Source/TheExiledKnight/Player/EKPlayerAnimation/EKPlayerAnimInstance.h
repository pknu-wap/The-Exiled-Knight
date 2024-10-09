// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EKPlayerAnimInstance.generated.h"

UCLASS()
class UEKPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UEKPlayerAnimInstance(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	TObjectPtr<class AEKPlayer> EKPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	TObjectPtr<class UCharacterMovementComponent> EKMovementComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CalcInfo")
	FVector Velocity = FVector(0, 0, 0);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CalcInfo")
	float CurrentSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CalcInfo")
	bool bShouldMove = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CalcInfo")
	bool bIsFalling = false;
};