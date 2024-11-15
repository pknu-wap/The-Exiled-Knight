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
#define BackStepStamina 50
#define JumpStamina 50

#define GreatSwordAttackStamina 100
#define GreatSwordEnhancedAttackStamina 200
#define GreatSwordJumpAttackStamina 100

#define SpearAttackStamina 50
#define SpearEnhancedAttackStamina 50
#define SpearJumpAttackStamina 50

#define StaffAttackStamina 80
#define StaffEnhancedAttackStamina 80
#define StaffJumpAttackStamina 80

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
	void MoveTriggered(const FInputActionValue& InputValue);
	void MoveRelease(const FInputActionValue& InputValue);

	void LookTriggered(const FInputActionValue& InputValue);
	void LookRelease(const FInputActionValue& InputValue);

	void JumpStarted(const FInputActionValue& InputValue);
	void JumpTriggered(const FInputActionValue& InputValue);

	void WeaponChangeStarted(const FInputActionValue& InputValue);

	void SprintAndDodgeStarted(const FInputActionValue& InputValue);
	void SprintAndDodgeTriggered(const FInputActionValue& InputValue);
	void SprintAndDodgeRelease(const FInputActionValue& InputValue);

	void UsePotionStarted(const FInputActionValue& InputValue);

	void WeaponAttackStarted(const FInputActionValue& InputValue);

	void WeaponDefenseStarted(const FInputActionValue& InputValue);
	void WeaponDefenseTriggered(const FInputActionValue& InputValue);
	void WeaponDefenseRelease(const FInputActionValue& InputValue);

	void SitDownStarted(const FInputActionValue& InputValue);

	void Interact(const FInputActionValue& InputValue);
	void FindInteractableObjects();
	
	void EnhanceStarted(const FInputActionValue& InputValue);
	void EnhanceRelease(const FInputActionValue& InputValue);

	void TestStarted(const FInputActionValue& InputValue);

public:
	TObjectPtr<class UAnimMontage> GetEquipAnimGreatSword();
	TObjectPtr<class UAnimMontage> GetUnEquipAnimGreatSword();
	TObjectPtr<class UAnimMontage> GetEquipAnimSpear();
	TObjectPtr<class UAnimMontage> GetUnEquipAnimSpear();
	TObjectPtr<class UAnimMontage> GetEquipAnimStaff();
	TObjectPtr<class UAnimMontage> GetUnEquipAnimStaff();

	TObjectPtr<class UAnimMontage> GetGreatSwordAttackAnim();
	TObjectPtr<class UAnimMontage> GetGreatSwordEnhancedAttackAnim();
	TObjectPtr<class UAnimMontage> GetGreatSwordJumpAttackAnim();
	TObjectPtr<class UAnimMontage> GetSpearAttackAnim();
	TObjectPtr<class UAnimMontage> GetStaffAttackAnim();

	TObjectPtr<class UAnimMontage> GetGreatSwordDefenseAnim();
	TObjectPtr<class UAnimMontage> GetSpearDefenseAnim();
	TObjectPtr<class UAnimMontage> GetStaffDefenseAnim();

	TObjectPtr<class UAnimMontage> GetGreatSwordHitAnim();
	TObjectPtr<class UAnimMontage> GetSpearHitAnim();
	TObjectPtr<class UAnimMontage> GetStaffHitAnim();

protected:
	// Common Input And Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|MappingContext")
	TObjectPtr<UInputMappingContext> IMCDefault;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IAWeaponAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IAWeaponDefense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IASitDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IAEnhance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IAGameMenu;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IAInteract;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IAGameMenu;

	// Test Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Test")
	TObjectPtr<UInputAction> IATest;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class AEKPlayer> EKPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AEKItem_Base* Item = nullptr;

protected:
	// Common Animation Montage
	UPROPERTY(VisibleAnywhere, Category = "Animation|Common")
	TObjectPtr<class UAnimMontage> UsePotionAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Common")
	TObjectPtr<class UAnimMontage> DodgeAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Common")
	TObjectPtr<class UAnimMontage> BackStepAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Common")
	TObjectPtr<class UAnimMontage> DieAnim;

protected:
	// GreatSword Animation Montage
	UPROPERTY(VisibleAnywhere, Category = "Animation|GreatSword")
	TObjectPtr<class UAnimMontage> GreatSwordAttackAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|GreatSword")
	TObjectPtr<class UAnimMontage> GreatSwordEnhancedAttackAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|GreatSword")
	TObjectPtr<class UAnimMontage> GreatSwordJumpAttackAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|GreatSword")
	TObjectPtr<class UAnimMontage> GreatSwordDefenseAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|GreatSword")
	TObjectPtr<class UAnimMontage> GreatSwordEquipAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|GreatSword")
	TObjectPtr<class UAnimMontage> GreatSwordUnEquipAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|GreatSword")
	TObjectPtr<class UAnimMontage> GreatSwordHitAnim;

protected:
	// Spear Animation Montage
	UPROPERTY(VisibleAnywhere, Category = "Animation|Spear")
	TObjectPtr<class UAnimMontage> SpearAttackAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Spear")
	TObjectPtr<class UAnimMontage> SpearDefenseAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Spear")
	TObjectPtr<class UAnimMontage> SpearEquipAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Spear")
	TObjectPtr<class UAnimMontage> SpearUnEquipAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Spear")
	TObjectPtr<class UAnimMontage> SpearHitAnim;

protected:
	// Staff Animation Montage
	UPROPERTY(VisibleAnywhere, Category = "Animation|Staff")
	TObjectPtr<class UAnimMontage> StaffAttackAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Staff")
	TObjectPtr<class UAnimMontage> StaffDefenseAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Staff")
	TObjectPtr<class UAnimMontage> StaffEquipAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Staff")
	TObjectPtr<class UAnimMontage> StaffUnEquipAnim;

	UPROPERTY(VisibleAnywhere, Category = "Animation|Staff")
	TObjectPtr<class UAnimMontage> StaffHitAnim;

public:
	bool bIsEquipWeapon = false;
	bool bCanAttackNext = false;

protected:
	FTimerHandle StaminaRecoveryHandle;
	FTimerHandle AttackNextHandle;
	FTimerHandle AttackEndHandle;

	UPROPERTY(EditAnywhere, Category = "Timer")
	float StaminaRecoveryTime = 2.5f;

	UPROPERTY(EditAnywhere, Category = "Timer")
	float AttackNextTime = 0.5f;

public:
	void SetStaminaRecoveryTime();
	void SetStaminaAndTimer(int32 Stamina);
	void SetAttackNextTime();
	void SetAttackNextAndTimer();
	void SetAttackEndTime();
	void SetAttackEndTimer(float Time);

public:
	void OnPressed_GameMenu(const FInputActionValue& InputValue);

protected:
	// About Sprint And Dodge
	float SpaceKeyPressStart = 0.f;
	float NeedDodgeThresholdTime = 0.2f;
	float KeyPressDuration = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USlotComponent> SlotComponent;
};