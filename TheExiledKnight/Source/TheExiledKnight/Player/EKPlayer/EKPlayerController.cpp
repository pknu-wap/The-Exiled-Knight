// Made by Somalia Pirate


#include "EKPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EKPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PawnMovementComponent.h"
#include "../Weapon/GreatSword.h"
#include "../Weapon/Spear.h"
#include "../Weapon/Staff.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EKPlayerStatusComponent.h"

AEKPlayerController::AEKPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Input Mapping Context
	ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCDefaultFinder(TEXT("/Game/EKPlayer/Input/IMC_EK_Default"));
	if (IMCDefaultFinder.Succeeded())
	{
		IMCDefault = IMCDefaultFinder.Object;
	}

	// Common Input
	ConstructorHelpers::FObjectFinder<UInputAction> IAMoveFinder(TEXT("/Game/EKPlayer/Input/IA_EK_Move"));
	if (IAMoveFinder.Succeeded())
	{
		IAMove = IAMoveFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> IALookFinder(TEXT("/Game/EKPlayer/Input/IA_EK_Look"));
	if (IALookFinder.Succeeded())
	{
		IALook = IALookFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> IAJumpFinder(TEXT("/Game/EKPlayer/Input/IA_EK_Jump"));
	if (IAJumpFinder.Succeeded())
	{
		IAJump = IAJumpFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> IAWeaponChangeFinder(TEXT("/Game/EKPlayer/Input/IA_EK_WeaponChange"));
	if (IAWeaponChangeFinder.Succeeded())
	{
		IAWeaponChange = IAWeaponChangeFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> IASprintAndDodgeFinder(TEXT("/Game/EKPlayer/Input/IA_EK_SprintAndDodge"));
	if (IASprintAndDodgeFinder.Succeeded())
	{
		IASprintAndDodge = IASprintAndDodgeFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> IAUsePotionFinder(TEXT("/Game/EKPlayer/Input/IA_EK_UsePotion"));
	if (IAUsePotionFinder.Succeeded())
	{
		IAUsePotion = IAUsePotionFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> IAWeaponAttackFinder(TEXT("/Game/EKPlayer/Input/IA_EK_Attack"));
	if (IAWeaponAttackFinder.Succeeded())
	{
		IAWeaponAttack = IAWeaponAttackFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> IAWeaponDefenseFinder(TEXT("/Game/EKPlayer/Input/IA_EK_Defense"));
	if (IAWeaponDefenseFinder.Succeeded())
	{
		IAWeaponDefense = IAWeaponDefenseFinder.Object;
	}

	// Common Animation Montage
	ConstructorHelpers::FObjectFinder<UAnimMontage> UsePotionAnimFinder(TEXT("/Game/EKPlayer/Animation/Common/UseItem/EKPlayer_Drink_Common_Montage"));
	if (UsePotionAnimFinder.Succeeded())
	{
		UsePotionAnim = UsePotionAnimFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> DodgeAnimFinder(TEXT("/Game/EKPlayer/Animation/Common/Step/EKPlayer_Dodge_Montage"));
	if (DodgeAnimFinder.Succeeded())
	{
		DodgeAnim = DodgeAnimFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> BackStepAnimFinder(TEXT("/Game/EKPlayer/Animation/Common/Step/EKPlayer_BackStep_Montage"));
	if (BackStepAnimFinder.Succeeded())
	{
		BackStepAnim = BackStepAnimFinder.Object;
	}

	// GreatSword Animation Montage
	ConstructorHelpers::FObjectFinder<UAnimMontage> GreatSwordAttackAnimFinder(TEXT("/Game/EKPlayer/Animation/GreatSword/Attack/EKPlayer_Combo"));
	if (GreatSwordAttackAnimFinder.Succeeded())
	{
		GreatSwordAttackAnim = GreatSwordAttackAnimFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> GreatSwordDefenseAnimFinder(TEXT("/Game/EKPlayer/Animation/GreatSword/Defense/EKPlayer_GreatSword_Defense_Montage"));
	if (GreatSwordDefenseAnimFinder.Succeeded())
	{
		GreatSwordDefenseAnim = GreatSwordDefenseAnimFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> GreatSwordEquipAnimFinder(TEXT("/Game/EKPlayer/Animation/GreatSword/Equip/EKPlayer_Equip_GreatSword_Montage"));
	if (GreatSwordEquipAnimFinder.Succeeded())
	{
		GreatSwordEquipAnim = GreatSwordEquipAnimFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> GreatSwordUnEquipAnimFinder(TEXT("/Game/EKPlayer/Animation/GreatSword/Equip/EKPlayer_UnEquip_GreatSword_Montage"));
	if (GreatSwordUnEquipAnimFinder.Succeeded())
	{
		GreatSwordUnEquipAnim = GreatSwordUnEquipAnimFinder.Object;
	}

	// Spear Animation Montage
	ConstructorHelpers::FObjectFinder<UAnimMontage> SpearAttackAnimFinder(TEXT("/Game/EKPlayer/Animation/Spear/Attack/EKPlayer_Attack_Spear_Montage"));
	if (SpearAttackAnimFinder.Succeeded())
	{
		SpearAttackAnim = SpearAttackAnimFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> SpearDefenseAnimFinder(TEXT("/Game/EKPlayer/Animation/Spear/Defense/EKPlayer_Spear_Defense_Montage"));
	if (SpearDefenseAnimFinder.Succeeded())
	{
		SpearDefenseAnim = SpearDefenseAnimFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> SpearEquipAnimFinder(TEXT("/Game/EKPlayer/Animation/Spear/Equip/EKPlayer_Equip_Spear"));
	if (SpearEquipAnimFinder.Succeeded())
	{
		SpearEquipAnim = SpearEquipAnimFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> SpearUnEquipAnimFinder(TEXT("/Game/EKPlayer/Animation/Spear/Equip/EKPlayer_UnEquip_Spear"));
	if (SpearUnEquipAnimFinder.Succeeded())
	{
		SpearUnEquipAnim = SpearUnEquipAnimFinder.Object;
	}

	// Staff Animation Montage
	ConstructorHelpers::FObjectFinder<UAnimMontage> StaffAttackAnimFinder(TEXT("/Game/EKPlayer/Animation/Staff/Attack/EKPlayer_Attack_Staff_Montage"));
	if (StaffAttackAnimFinder.Succeeded())
	{
		StaffAttackAnim = StaffAttackAnimFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> StaffDefenseAnimFinder(TEXT("/Game/EKPlayer/Animation/Staff/Defense/EKPlayer_Staff_Defense_Montage"));
	if (StaffDefenseAnimFinder.Succeeded())
	{
		StaffDefenseAnim = StaffDefenseAnimFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> StaffEquipAnimFinder(TEXT("/Game/EKPlayer/Animation/Staff/Equip/EKPlayer_Equip_Staff_Montage"));
	if (StaffEquipAnimFinder.Succeeded())
	{
		StaffEquipAnim = StaffEquipAnimFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> StaffUnEquipAnimFinder(TEXT("/Game/EKPlayer/Animation/Staff/Equip/EKPlayer_UnEquip_Staff_Montage"));
	if (StaffUnEquipAnimFinder.Succeeded())
	{
		StaffUnEquipAnim = StaffUnEquipAnimFinder.Object;
	}
}

void AEKPlayerController::BeginPlay()
{
	Super::BeginPlay();

	EKPlayer = Cast<AEKPlayer>(GetPawn());

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMCDefault, 0);
	}
}

void AEKPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &ThisClass::MoveTriggered);
		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Triggered, this, &ThisClass::LookTriggered);
		EnhancedInputComponent->BindAction(IAJump, ETriggerEvent::Started, this, &ThisClass::JumpStarted);

		EnhancedInputComponent->BindAction(IAWeaponChange, ETriggerEvent::Triggered, this, &ThisClass::WeaponChangeStarted);
		EnhancedInputComponent->BindAction(IAUsePotion, ETriggerEvent::Started, this, &ThisClass::UsePotionStarted);

		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Started, this, &ThisClass::SprintAndDodgeStarted);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Triggered, this, &ThisClass::SprintAndDodgeTriggered);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Completed, this, &ThisClass::SprintAndDodgeRelease);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Canceled, this, &ThisClass::SprintAndDodgeRelease);

		EnhancedInputComponent->BindAction(IAWeaponAttack, ETriggerEvent::Started, this, &ThisClass::WeaponAttackStarted);

		EnhancedInputComponent->BindAction(IAWeaponDefense, ETriggerEvent::Started, this, &ThisClass::WeaponDefenseStarted);
		EnhancedInputComponent->BindAction(IAWeaponDefense, ETriggerEvent::Triggered, this, &ThisClass::WeaponDefenseTriggered);
		EnhancedInputComponent->BindAction(IAWeaponDefense, ETriggerEvent::Completed, this, &ThisClass::WeaponDefenseRelease);
		EnhancedInputComponent->BindAction(IAWeaponDefense, ETriggerEvent::Canceled, this, &ThisClass::WeaponDefenseRelease);
	}
}

void AEKPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AEKPlayerController::MoveTriggered(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	FRotator Rotator = GetControlRotation();

	if (MovementVector.X != 0)
	{
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.X);
	}

	if (MovementVector.Y != 0)
	{
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.Y);
	}
}

void AEKPlayerController::LookTriggered(const FInputActionValue& InputValue)
{
	FVector2D LookAxisVector = InputValue.Get<FVector2D>();

	if (EKPlayer)
	{
		EKPlayer->AddControllerYawInput(LookAxisVector.X);
		EKPlayer->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AEKPlayerController::JumpStarted(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < JumpStamina)
	{
		return;
	}

	EKPlayer->Jump();
	SetStaminaAndTimer(JumpStamina);
}

void AEKPlayerController::WeaponChangeStarted(const FInputActionValue& InputValue)
{
	if (EKPlayer)
	{
		EKPlayer->GetCurrentWeapon()->PlayWeaponEquipAnimMontage(EKPlayer, this);
	}
}

void AEKPlayerController::SprintAndDodgeStarted(const FInputActionValue& InputValue)
{
	SpaceKeyPressStart = GetWorld()->GetTimeSeconds();
}

void AEKPlayerController::SprintAndDodgeTriggered(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < SprintStamina)
	{
		EKPlayer->GetCharacterMovement()->MaxWalkSpeed = EKPlayerWalkSpeed;
		return;
	}

	KeyPressDuration = GetWorld()->GetTimeSeconds() - SpaceKeyPressStart;
	
	if (KeyPressDuration >= NeedDodgeThresholdTime)
	{
		EKPlayer->GetCharacterMovement()->MaxWalkSpeed = EKPlayerSprintSpeed;
		SetStaminaAndTimer(SprintStamina);
	}
}

void AEKPlayerController::SprintAndDodgeRelease(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	FVector MoveInput = EKPlayer->GetLastMovementInputVector();

	if (KeyPressDuration < NeedDodgeThresholdTime && EKPlayer->GetPlayerStatusComponent()->GetStamina() >= DodgeStamina)
	{
		if (MoveInput.IsNearlyZero())
		{
			EKPlayer->PlayAnimMontage(BackStepAnim);
			SetStaminaAndTimer(BackStepStamina);
		}
		else
		{
			EKPlayer->PlayAnimMontage(DodgeAnim);
			SetStaminaAndTimer(DodgeStamina);
		}
	}

	EKPlayer->GetCharacterMovement()->MaxWalkSpeed = EKPlayerWalkSpeed;
}

void AEKPlayerController::UsePotionStarted(const FInputActionValue& InputValue)
{
	if (EKPlayer)
	{
		EKPlayer->GetPlayerStatusComponent()->SetHp(10);
		EKPlayer->GetPlayerStatusComponent()->SetMp(10);
	}

	if (UsePotionAnim)
	{
		EKPlayer->PlayAnimMontage(UsePotionAnim);
	}
}

void AEKPlayerController::WeaponAttackStarted(const FInputActionValue& InputValue)
{
	if (EKPlayer)
	{
		EKPlayer->GetCurrentWeapon()->PlayAttackStartAnimMontage(EKPlayer, this);
	}
}

void AEKPlayerController::WeaponDefenseStarted(const FInputActionValue& InputValue)
{
	if (EKPlayer)
	{
		EKPlayer->GetCurrentWeapon()->PlayDefenseStartAnimMontage(EKPlayer, this);
	}
}

void AEKPlayerController::WeaponDefenseTriggered(const FInputActionValue& InputValue)
{
	if (EKPlayer)
	{
		EKPlayer->GetCurrentWeapon()->PlayDefenseTriggerAnimMontage(EKPlayer, this);
	}
}

void AEKPlayerController::WeaponDefenseRelease(const FInputActionValue& InputValue)
{
	if (EKPlayer)
	{
		EKPlayer->GetCurrentWeapon()->PlayDefenseReleaseAnimMontage(EKPlayer, this);
	}
}

TObjectPtr<UAnimMontage> AEKPlayerController::GetEquipAnimGreatSword()
{
	return GreatSwordEquipAnim;
}

TObjectPtr<UAnimMontage> AEKPlayerController::GetUnEquipAnimGreatSword()
{
	return GreatSwordUnEquipAnim;
}

TObjectPtr<UAnimMontage> AEKPlayerController::GetEquipAnimSpear()
{
	return SpearEquipAnim;
}

TObjectPtr<UAnimMontage> AEKPlayerController::GetUnEquipAnimSpear()
{
	return SpearUnEquipAnim;
}

TObjectPtr<UAnimMontage> AEKPlayerController::GetEquipAnimStaff()
{
	return StaffEquipAnim;
}

TObjectPtr<UAnimMontage> AEKPlayerController::GetUnEquipAnimStaff()
{
	return StaffUnEquipAnim;
}

TObjectPtr<UAnimMontage> AEKPlayerController::GetGreatSwordAttackAnim()
{
	return GreatSwordAttackAnim;
}

TObjectPtr<UAnimMontage> AEKPlayerController::GetSpearAttackAnim()
{
	return SpearAttackAnim;
}

TObjectPtr<UAnimMontage> AEKPlayerController::GetStaffAttackAnim()
{
	return StaffAttackAnim;
}

TObjectPtr<UAnimMontage> AEKPlayerController::GetGreatSwordDefenseAnim()
{
	return GreatSwordDefenseAnim;
}

TObjectPtr<UAnimMontage> AEKPlayerController::GetSpearDefenseAnim()
{
	return SpearDefenseAnim;
}

TObjectPtr<UAnimMontage> AEKPlayerController::GetStaffDefenseAnim()
{
	return StaffDefenseAnim;
}

void AEKPlayerController::SetStaminaRecoveryTime()
{
	EKPlayer->GetPlayerStatusComponent()->bCanStaminaRecovery = true;
}

void AEKPlayerController::SetStaminaAndTimer(int32 Stamina)
{
	EKPlayer->GetPlayerStatusComponent()->SetStamina(-Stamina);
	EKPlayer->GetPlayerStatusComponent()->bCanStaminaRecovery = false;
	GetWorldTimerManager().SetTimer(StaminaRecoveryHandle, this, &ThisClass::SetStaminaRecoveryTime, StaminaRecoveryTime, false);
}

void AEKPlayerController::SetAttackNextTime()
{
	bCanAttackNext = false;
}

void AEKPlayerController::SetAttackNextAndTimer()
{
	bCanAttackNext = true;
	EKPlayer->GetPlayerStatusComponent()->SetGreatSwordCombo();
	EKPlayer->GetPlayerStatusComponent()->SetSpearCombo();
	EKPlayer->GetPlayerStatusComponent()->SetStaffCombo();
	GetWorldTimerManager().SetTimer(AttackNextHandle, this, &ThisClass::SetAttackNextTime, AttackNextTime, false);
}

void AEKPlayerController::SetAttackEndTime()
{
	EKPlayer->GetPlayerStatusComponent()->ResetGreatSwordCombo();
	EKPlayer->GetPlayerStatusComponent()->ResetSpearCombo();
	EKPlayer->GetPlayerStatusComponent()->ResetStaffCombo();
}

void AEKPlayerController::SetAttackEndTimer(float Time)
{
	GetWorldTimerManager().SetTimer(AttackEndHandle, this, &ThisClass::SetAttackEndTime, Time, false);
}