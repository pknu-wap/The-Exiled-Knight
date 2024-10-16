// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EKPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

// Edit Stamina Consumption Here
#define SprintStamina 1
#define JumpStamina 100

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
	void JumpStart(const FInputActionValue& InputValue);

	void WeaponChangeAction(const FInputActionValue& InputValue);
	void SprintAndDodgeAction(const FInputActionValue& InputValue);
	void SprintAndDodgeRelease(const FInputActionValue& InputValue);
	void UsePotionStart(const FInputActionValue& InputValue);

	void GreatSwordAttackAction(const FInputActionValue& InputValue);
	void SpearAttackAction(const FInputActionValue& InputValue);
	void StaffAttackAction(const FInputActionValue& InputValue);

public:
	TObjectPtr<class UAnimMontage> GetEquipAnimGreatSword();
	TObjectPtr<class UAnimMontage> GetUnEquipAnimGreatSword();
	TObjectPtr<class UAnimMontage> GetEquipAnimSpear();
	TObjectPtr<class UAnimMontage> GetUnEquipAnimSpear();
	TObjectPtr<class UAnimMontage> GetEquipAnimStaff();
	TObjectPtr<class UAnimMontage> GetUnEquipAnimStaff();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|MappingContext")
	TObjectPtr<UInputMappingContext> IMCDefault;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|MappingContext")
	TObjectPtr<UInputMappingContext> IMCGreatSword;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|MappingContext")
	TObjectPtr<UInputMappingContext> IMCSpear;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|MappingContext")
	TObjectPtr<UInputMappingContext> IMCStaff;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IAMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IALook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IAJump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IAWeaponChange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IASprintAndDodge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IAUsePotion;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|GreatSword")
	TObjectPtr<UInputAction> IAGreatSwordAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Spear")
	TObjectPtr<UInputAction> IASpearAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Staff")
	TObjectPtr<UInputAction> IAStaffAttack;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class AEKPlayer> EKPlayer;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Animation|Common")
	TObjectPtr<class UAnimMontage> UsePotionAnim;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Animation|GreatSword")
	TObjectPtr<class UAnimMontage> GreatSwordAttackAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|GreatSword")
	TObjectPtr<class UAnimMontage> GreatSwordEquipAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|GreatSword")
	TObjectPtr<class UAnimMontage> GreatSwordUnEquipAnim;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Animation|Spear")
	TObjectPtr<class UAnimMontage> SpearAttackAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Spear")
	TObjectPtr<class UAnimMontage> SpearEquipAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Spear")
	TObjectPtr<class UAnimMontage> SpearUnEquipAnim;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Animation|Staff")
	TObjectPtr<class UAnimMontage> StaffAttackAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Staff")
	TObjectPtr<class UAnimMontage> StaffEquipAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Staff")
	TObjectPtr<class UAnimMontage> StaffUnEquipAnim;

public:
	bool bIsEquipWeapon = false;

protected:
	FTimerHandle StaminaRecoveryHandle;

	UPROPERTY(EditAnywhere, Category = "Timer")
	float StaminaRecoveryTime = 2.5f;

	void SetStaminaRecoveryTime();
};