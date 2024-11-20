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

// Edit Stamina & Mp Consumption Here
#define SprintStamina 1
#define DodgeStamina 100
#define BackStepStamina 50
#define JumpStamina 50

#define DefenseStamina 200

#define GreatSwordAttackStamina 100
#define GreatSwordSkill 80
#define GreatSwordSkillMp 200

#define SpearAttackStamina 50
#define SpearSkill 80
#define SpearSkillMp 200

#define StaffAttackStamina 80
#define StaffAttackMp 50
#define StaffSkill 80
#define StaffSkillMp 300

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

	UFUNCTION()
	void FindInteractableObjects();

	void SkillStarted(const FInputActionValue& InputValue);

	void LockOnStarted(const FInputActionValue& InputValue);


public:
	void OnPressed_GameMenu(const FInputActionValue& InputValue);
	void OnPressed_Up(const FInputActionValue& InputValue);
	void OnPressed_Down(const FInputActionValue& InputValue);
	void OnPressed_Left(const FInputActionValue& InputValue);
	void OnPressed_Right(const FInputActionValue& InputValue);

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
	UInputAction* IAGameMenu;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Common")
	UInputAction* IALockOn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	UInputAction* IA_Up;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	UInputAction* IA_Down;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	UInputAction* IA_Left;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Common")
	UInputAction* IA_Right;

	// Test Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Test")
	UInputAction* IATest;
#pragma endregion

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class AEKPlayer> EKPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AEKItem_Base* Item = nullptr;

	class IUInteractableInterface* InteractableActor = nullptr;

	void DestroyItem();

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
	bool bCanItemInteract = false;

#pragma region Timer

public:
	// About Battle State
	const float BattleEndTime = 10.f;
	bool bCanAttackNext = false;

	const float InteractCheckTime = 0.5f;

protected:
	FTimerHandle StaminaRecoveryHandle;
	FTimerHandle AttackEndHandle;
	FTimerHandle StaffBaseSkillEndHandle;
	FTimerHandle BattleStateHandle;
	FTimerHandle InvincibilityHandle; // muzuk
	FTimerHandle InteractCheckHandle;

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

public:
	// About Battle State
	void SetBattleStateEnd();
	void BattleStateTimer();

	// About Staff Base Skill
	void RemoveAttackTag();
	void RemoveAttackTagTimer(float Time);

	void SetInvincibility();
	void InvincibilityTimer(float Time);

	// About Interact 
	void TryInteractLoop();

#pragma endregion

protected:
	// About Sprint And Dodge
	float SpaceKeyPressStart = 0.f;
	float NeedDodgeThresholdTime = 0.2f;
	float KeyPressDuration = 0.f;

	FVector2D LookAxisVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USlotComponent> SlotComponent;
};