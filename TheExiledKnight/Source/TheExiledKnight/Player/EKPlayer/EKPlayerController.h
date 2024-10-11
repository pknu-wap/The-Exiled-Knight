// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EKPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class AEKPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AEKPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	void MoveAction(const FInputActionValue& InputValue);
	void LookAction(const FInputActionValue& InputValue);
	void JumpAction(const FInputActionValue& InputValue);
	void WeaponChangeAction(const FInputActionValue& InputValue);
	void SprintAndDodgeAction(const FInputActionValue& InputValue);
	void SprintAndDodgeRelease(const FInputActionValue& InputValue);
	void GreatSwordAttackAction(const FInputActionValue& InputValue);
	void SpearAttackAction(const FInputActionValue& InputValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> IMCDefault;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> IMCGreatSword;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> IMCSpear;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IAMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IALook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IAJump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IAWeaponChange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IASprintAndDodge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IAGreatSwordAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IASpearAttack;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<class AEKPlayer> EKPlayer;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimMontage> GreatSwordAttackAnim;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimMontage> GreatSwordEquipAnim;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimMontage> GreatSwordUnEquipAnim;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimMontage> SpearAttackAnim;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimMontage> SpearEquipAnim;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimMontage> SpearUnEquipAnim;

public:
	bool bIsEquipGreatSword = false;

	bool bIsEquipSpear = false;

	UPROPERTY()
	float FollowTime;

	UPROPERTY()
	float ShortPressThreshold = 0.3f;
};
