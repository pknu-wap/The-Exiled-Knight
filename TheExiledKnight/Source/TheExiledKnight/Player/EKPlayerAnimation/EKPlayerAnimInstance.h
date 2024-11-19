// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../EKPlayerEnum.h"
#include "EKPlayerAnimInstance.generated.h"

#define GreatSwordNumber 1
#define SpearNumber 2
#define StaffNumber 3

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
	TObjectPtr<class AEKPlayerController> EKPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	TObjectPtr<class UCharacterMovementComponent> EKMovementComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info|Calc")
	FVector Velocity = FVector(0, 0, 0);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info|Calc")
	float CurrentSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info|Calc")
	float HitAngle = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info|Calc")
	float Stamina = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info|Weapon")
	int32 CurrentWeaponType;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info|Bool")
	bool bShouldMove = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info|Bool")
	bool bIsFalling = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info|Bool")
	bool bIsHitted = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info|Bool")
	bool bIsHitDowned = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info|Bool")
	bool bIsDefense = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info|Bool")
	bool bIsSitted = false;
};