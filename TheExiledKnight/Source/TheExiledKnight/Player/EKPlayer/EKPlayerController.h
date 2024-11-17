// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "EKPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;

#pragma region Default Value

// Edit Walk and Sprint Speed Here
#define EKPlayerWalkSpeed 200.f
#define EKPlayerSprintSpeed 600.f

// Edit Stamina Consumption Here
#define SprintStamina 1
#define DodgeStamina 100
#define BackStepStamina 50
#define JumpStamina 50

#define DefenseStamina 200

#define GreatSwordAttackStamina 100
#define GreatSwordEnhancedAttackStamina 200
#define GreatSwordJumpAttackStamina 100

#define SpearAttackStamina 50
#define SpearEnhancedAttackStamina 50
#define SpearJumpAttackStamina 50

#define StaffAttackStamina 80
#define StaffEnhancedAttackStamina 80
#define StaffJumpAttackStamina 80

#pragma endregion

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

#pragma region Input Function

private:
	// About Input Function
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
	void WeaponDefenseRelease(const FInputActionValue& InputValue);

	void SitDownStarted(const FInputActionValue& InputValue);

	void Interact(const FInputActionValue& InputValue);
	void FindInteractableObjects();

	void SkillStarted(const FInputActionValue& InputValue);
	void SkillRelease(const FInputActionValue& InputValue);

	void TestStarted(const FInputActionValue& InputValue);

public:
	void OnPressed_GameMenu(const FInputActionValue& InputValue);

#pragma endregion

#pragma region Input

protected:
	// Common Input And Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|MappingContext")
	UInputMappingContext* IMCDefault;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Common")
	UInputAction* IAMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Common")
	UInputAction* IALook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Common")
	UInputAction* IAJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Common")
	UInputAction* IAWeaponChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Common")
	UInputAction* IASprintAndDodge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Common")
	UInputAction* IAUsePotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Common")
	UInputAction* IAWeaponAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Common")
	UInputAction* IAWeaponDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Common")
	UInputAction* IASitDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Common")
	UInputAction* IASkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Common")
	UInputAction* IAInteract;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IAGameMenu;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	TObjectPtr<UInputAction> IAInteract;

	// Test Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Test")
	UInputAction* IATest;

#pragma endregion

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class AEKPlayer> EKPlayer;

protected:
	// Common Animation Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Common")
	TObjectPtr<UAnimMontage> UsePotionAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Common")
	TObjectPtr<UAnimMontage> DodgeAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Common")
	TObjectPtr<UAnimMontage> BackStepAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Common")
	TObjectPtr<UAnimMontage> DieAnim;

public:
	bool bIsEquipWeapon = false;

#pragma region Timer

public:
	// About Perfect Defense
	bool bIsPerfectDefense = false;
	const float PerfectDefenseTime = 0.2f;

	// About Battle State
	const float BattleEndTime = 10.f;
	bool bCanAttackNext = false;
	bool bCanItemInteract = false;

protected:
	FTimerHandle StaminaRecoveryHandle;
	FTimerHandle AttackEndHandle;
	FTimerHandle PerfectDefenseHandle;
	FTimerHandle BattleStateHandle;

	// How long does it take for the player to recover after using the Stemina
	const float StaminaRecoveryTime = 2.5f;

	// Time for player to move on to the next combo after an attack
	const float AttackNextTime = 0.5f;

public:
	// About Stamina and Attack
	void SetStaminaRecoveryTime();
	void ConsumtionStaminaAndTimer(int32 Stamina);
	void SetAttackComboNext();
	void ResetAttackCombo();
	void SetAttackEndTimer(float Time);

	// About Perfect Defense
	void SetPerfectDefense();
	void PerfectDefenseTimer();

	// About Battle State
	void SetBattleStateEnd();
	void BattleStateTimer();

#pragma endregion

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