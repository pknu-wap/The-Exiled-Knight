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
	ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCDefaultFinder(TEXT("/Game/EKPlayer/Input/IMC_EK_Default"));
	if (IMCDefaultFinder.Succeeded())
	{
		IMCDefault = IMCDefaultFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCGreatSwordFinder(TEXT("/Game/EKPlayer/Input/GreatSword/IMC_EK_GreatSword"));
	if (IMCGreatSwordFinder.Succeeded())
	{
		IMCGreatSword = IMCGreatSwordFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCSpearFinder(TEXT("/Game/EKPlayer/Input/Spear/IMC_EK_Spear"));
	if (IMCSpearFinder.Succeeded())
	{
		IMCSpear = IMCSpearFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCStaffFinder(TEXT("/Game/EKPlayer/Input/Staff/IMC_EK_Staff"));
	if (IMCStaffFinder.Succeeded())
	{
		IMCStaff = IMCStaffFinder.Object;
	}

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

	ConstructorHelpers::FObjectFinder<UInputAction> IAGreatSwordAttackFinder(TEXT("/Game/EKPlayer/Input/GreatSword/IA_EK_GreatSword_Attack"));
	if (IAGreatSwordAttackFinder.Succeeded())
	{
		IAGreatSwordAttack = IAGreatSwordAttackFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> IASpearAttackFinder(TEXT("/Game/EKPlayer/Input/Spear/IA_EK_Spear_Attack"));
	if (IASpearAttackFinder.Succeeded())
	{
		IASpearAttack = IASpearAttackFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> IAStaffAttackFinder(TEXT("/Game/EKPlayer/Input/Staff/IA_EK_Staff_Attack"));
	if (IAStaffAttackFinder.Succeeded())
	{
		IAStaffAttack = IAStaffAttackFinder.Object;
	}

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

	ConstructorHelpers::FObjectFinder<UAnimMontage> GreatSwordAttackAnimFinder(TEXT("/Game/EKPlayer/Animation/GreatSword/Attack/EKPlayer_Combo"));
	if (GreatSwordAttackAnimFinder.Succeeded())
	{
		GreatSwordAttackAnim = GreatSwordAttackAnimFinder.Object;
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

	ConstructorHelpers::FObjectFinder<UAnimMontage> SpearAttackAnimFinder(TEXT("/Game/EKPlayer/Animation/Spear/Attack/EKPlayer_Attack_Spear_Montage"));
	if (SpearAttackAnimFinder.Succeeded())
	{
		SpearAttackAnim = SpearAttackAnimFinder.Object;
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

	ConstructorHelpers::FObjectFinder<UAnimMontage> StaffAttackAnimFinder(TEXT("/Game/EKPlayer/Animation/Staff/Attack/EKPlayer_Attack_Staff_Montage"));
	if (StaffAttackAnimFinder.Succeeded())
	{
		StaffAttackAnim = StaffAttackAnimFinder.Object;
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
		// Test Version
		if (EKPlayer->GetMesh()->AnimClass == EKPlayer->ABPGreatSword)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(IMCGreatSword, 0);
		}
		else if (EKPlayer->GetMesh()->AnimClass == EKPlayer->ABPSpear)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(IMCSpear, 0);
		}
		else if (EKPlayer->GetMesh()->AnimClass == EKPlayer->ABPStaff)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(IMCStaff, 0);
		}
	}
}

void AEKPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &ThisClass::MoveAction);
		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Triggered, this, &ThisClass::LookAction);
		EnhancedInputComponent->BindAction(IAJump, ETriggerEvent::Started, this, &ThisClass::JumpStart);

		EnhancedInputComponent->BindAction(IAWeaponChange, ETriggerEvent::Triggered, this, &ThisClass::WeaponChangeAction);
		EnhancedInputComponent->BindAction(IAUsePotion, ETriggerEvent::Started, this, &ThisClass::UsePotionStart);

		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Started, this, &ThisClass::SprintAndDodgeBegin);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Triggered, this, &ThisClass::SprintAndDodgeAction);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Completed, this, &ThisClass::SprintAndDodgeRelease);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Canceled, this, &ThisClass::SprintAndDodgeRelease);

		EnhancedInputComponent->BindAction(IAGreatSwordAttack, ETriggerEvent::Started, this, &ThisClass::GreatSwordAttackAction);

		EnhancedInputComponent->BindAction(IASpearAttack, ETriggerEvent::Started, this, &ThisClass::SpearAttackAction);

		EnhancedInputComponent->BindAction(IAStaffAttack, ETriggerEvent::Started, this, &ThisClass::StaffAttackAction);
	}
}

void AEKPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AEKPlayerController::MoveAction(const FInputActionValue& InputValue)
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

void AEKPlayerController::LookAction(const FInputActionValue& InputValue)
{
	FVector2D LookAxisVector = InputValue.Get<FVector2D>();

	if (EKPlayer)
	{
		EKPlayer->AddControllerYawInput(LookAxisVector.X);
		EKPlayer->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AEKPlayerController::JumpStart(const FInputActionValue& InputValue)
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

void AEKPlayerController::WeaponChangeAction(const FInputActionValue& InputValue)
{
	if (EKPlayer)
	{
		EKPlayer->GetCurrentWeapon()->PlayWeaponEquipAnimMontage(EKPlayer, this);
	}
}

void AEKPlayerController::SprintAndDodgeBegin(const FInputActionValue& InputValue)
{
	SpaceKeyPressStart = GetWorld()->GetTimeSeconds();
}

void AEKPlayerController::SprintAndDodgeAction(const FInputActionValue& InputValue)
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
	
	if (KeyPressDuration >= NeedDodgeThresholdTime) // Sprint
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

	if (KeyPressDuration < NeedDodgeThresholdTime && EKPlayer->GetPlayerStatusComponent()->GetStamina() >= DodgeStamina)
	{
		EKPlayer->PlayAnimMontage(DodgeAnim);
		SetStaminaAndTimer(DodgeStamina);
	}

	EKPlayer->GetCharacterMovement()->MaxWalkSpeed = EKPlayerWalkSpeed;
}

void AEKPlayerController::UsePotionStart(const FInputActionValue& InputValue)
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

void AEKPlayerController::GreatSwordAttackAction(const FInputActionValue& InputValue)
{
	if (!bIsEquipWeapon || !GreatSwordAttackAnim)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < GreatSwordAttackStamina)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetGreatSwordCombo() == 1)
	{
		EKPlayer->PlayAnimMontage(GreatSwordAttackAnim, 1.0f, FName("Attack1"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetGreatSwordCombo() == 2 && bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(GreatSwordAttackAnim, 1.0f, FName("Attack2"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetGreatSwordCombo() == 3 && bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(GreatSwordAttackAnim, 1.0f, FName("Attack3"));
	}

	SetStaminaAndTimer(GreatSwordAttackStamina);
}

void AEKPlayerController::SpearAttackAction(const FInputActionValue& InputValue)
{
	if (!bIsEquipWeapon || !SpearAttackAnim)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < SpearAttackStamina)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 1)
	{
		EKPlayer->PlayAnimMontage(SpearAttackAnim, 1.0f, FName("Attack1"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 2 && bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(SpearAttackAnim, 1.0f, FName("Attack2"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 3 && bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(SpearAttackAnim, 1.0f, FName("Attack3"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 4 && bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(SpearAttackAnim, 1.0f, FName("Attack4"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 5 && bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(SpearAttackAnim, 1.0f, FName("Attack5"));
	}

	SetStaminaAndTimer(SpearAttackStamina);
}

void AEKPlayerController::StaffAttackAction(const FInputActionValue& InputValue)
{
	if (!bIsEquipWeapon || !StaffAttackAnim)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < StaffAttackStamina)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStaffCombo() == 1)
	{
		EKPlayer->PlayAnimMontage(StaffAttackAnim, 1.0f, FName("Attack1"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetStaffCombo() == 2 && bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(StaffAttackAnim, 1.0f, FName("Attack2"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetStaffCombo() == 3 && bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(StaffAttackAnim, 1.0f, FName("Attack3"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetStaffCombo() == 4 && bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(StaffAttackAnim, 1.0f, FName("Attack4"));
	}

	SetStaminaAndTimer(StaffAttackStamina);
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