// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EKPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

// Edit Walk and Sprint Speed Here
#define EKPlayerWalkSpeed 200.f
#define EKPlayerSprintSpeed 600.f

// Edit Stamina Consumption Here
#define SprintStamina 1
#define DodgeStamina 100
#define JumpStamina 100
#define GreatSwordAttackStamina 100
#define SpearAttackStamina 50
#define StaffAttackStamina 80

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
	void SprintAndDodgeBegin(const FInputActionValue& InputValue);
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

	UPROPERTY(VisibleAnywhere, Category = "Animation|Common")
	TObjectPtr<class UAnimMontage> DodgeAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Common")
	TObjectPtr<class UAnimMontage> BackStepAnim;

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
	FTimerHandle AttackNextHandle;
	FTimerHandle AttackEndHandle;

	UPROPERTY(EditAnywhere, Category = "Timer")
	float StaminaRecoveryTime = 2.5f;

	UPROPERTY(EditAnywhere, Category = "Timer")
	float AttackNextTime = 0.5f;

	void SetStaminaRecoveryTime();
	void SetStaminaAndTimer(int32 Stamina);

	bool bCanAttackNext = false;

public:
	void SetAttackNextTime();
	void SetAttackNextAndTimer();
	void SetAttackEndTime();
	void SetAttackEndTimer(float Time);

protected:
	// About Sprint And Dodge
	float SpaceKeyPressStart = 0.f;
	float NeedDodgeThresholdTime = 0.2f;
	float KeyPressDuration = 0.f;
};