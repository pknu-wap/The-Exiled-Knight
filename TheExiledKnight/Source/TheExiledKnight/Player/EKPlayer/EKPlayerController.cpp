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

	ConstructorHelpers::FObjectFinder<UAnimMontage> UsePotionAnimFinder(TEXT("/Game/EKPlayer/Animation/Common/EKPlayer_Drink_Common_Montage"));
	if (UsePotionAnimFinder.Succeeded())
	{
		UsePotionAnim = UsePotionAnimFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> GreatSwordAttackAnimFinder(TEXT("/Game/EKPlayer/Animation/GreatSword/Attack/EKPlayer_Combo1"));
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
			Subsystem->AddMappingContext(IMCGreatSword, 0);
		}
		else if (EKPlayer->GetMesh()->AnimClass == EKPlayer->ABPSpear)
		{
			Subsystem->AddMappingContext(IMCSpear, 0);
		}
		else if (EKPlayer->GetMesh()->AnimClass == EKPlayer->ABPStaff)
		{
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
		EnhancedInputComponent->BindAction(IAJump, ETriggerEvent::Triggered, this, &ThisClass::JumpAction);

		EnhancedInputComponent->BindAction(IAWeaponChange, ETriggerEvent::Triggered, this, &ThisClass::WeaponChangeAction);
		EnhancedInputComponent->BindAction(IAUsePotion, ETriggerEvent::Started, this, &ThisClass::UsePotionStart);
		EnhancedInputComponent->BindAction(IAUsePotion, ETriggerEvent::Triggered, this, &ThisClass::UsePotionAction);

		//EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Started, this, &ThisClass::SprintAndDodgeAction);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Triggered, this, &ThisClass::SprintAndDodgeAction);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Completed, this, &ThisClass::SprintAndDodgeRelease);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Canceled, this, &ThisClass::SprintAndDodgeRelease);

		EnhancedInputComponent->BindAction(IAGreatSwordAttack, ETriggerEvent::Triggered, this, &ThisClass::GreatSwordAttackAction);

		EnhancedInputComponent->BindAction(IASpearAttack, ETriggerEvent::Triggered, this, &ThisClass::SpearAttackAction);

		EnhancedInputComponent->BindAction(IAStaffAttack, ETriggerEvent::Triggered, this, &ThisClass::StaffAttackAction);
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

void AEKPlayerController::JumpAction(const FInputActionValue& InputValue)
{
	if (EKPlayer)
	{
		EKPlayer->Jump();
	}
}

void AEKPlayerController::WeaponChangeAction(const FInputActionValue& InputValue)
{
	if (EKPlayer)
	{
		EKPlayer->GetCurrentWeapon()->PlayWeaponEquipAnimMontage(EKPlayer, this);
	}
}

void AEKPlayerController::SprintAndDodgeAction(const FInputActionValue& InputValue)
{
	if (EKPlayer)
	{
		EKPlayer->GetCharacterMovement()->MaxWalkSpeed = 600;
	}
}

void AEKPlayerController::SprintAndDodgeRelease(const FInputActionValue& InputValue)
{
	if (EKPlayer)
	{
		EKPlayer->GetCharacterMovement()->MaxWalkSpeed = 200;
	}
}

void AEKPlayerController::UsePotionStart(const FInputActionValue& InputValue)
{
	if (EKPlayer)
	{
		EKPlayer->GetPlayerStatusComponent()->SetHp(10);
		EKPlayer->GetPlayerStatusComponent()->SetMp(10);
	}
}

void AEKPlayerController::UsePotionAction(const FInputActionValue& InputValue)
{
	if (UsePotionAnim)
	{
		EKPlayer->PlayAnimMontage(UsePotionAnim);
	}
}

void AEKPlayerController::GreatSwordAttackAction(const FInputActionValue& InputValue)
{
	if (!bIsEquipWeapon)
	{
		return;
	}

	if (GreatSwordAttackAnim)
	{
		EKPlayer->PlayAnimMontage(GreatSwordAttackAnim);
	}
}

void AEKPlayerController::SpearAttackAction(const FInputActionValue& InputValue)
{
	if (!bIsEquipWeapon)
	{
		return;
	}

	if (SpearAttackAnim)
	{
		EKPlayer->PlayAnimMontage(SpearAttackAnim);
	}
}

void AEKPlayerController::StaffAttackAction(const FInputActionValue& InputValue)
{
	if (!bIsEquipWeapon)
	{
		return;
	}

	if (StaffAttackAnim)
	{
		EKPlayer->PlayAnimMontage(StaffAttackAnim);
	}
}

TObjectPtr<class UAnimMontage> AEKPlayerController::GetEquipAnimGreatSword()
{
	return GreatSwordEquipAnim;
}

TObjectPtr<class UAnimMontage> AEKPlayerController::GetUnEquipAnimGreatSword()
{
	return GreatSwordUnEquipAnim;
}

TObjectPtr<class UAnimMontage> AEKPlayerController::GetEquipAnimSpear()
{
	return SpearEquipAnim;
}

TObjectPtr<class UAnimMontage> AEKPlayerController::GetUnEquipAnimSpear()
{
	return SpearUnEquipAnim;
}

TObjectPtr<class UAnimMontage> AEKPlayerController::GetEquipAnimStaff()
{
	return StaffEquipAnim;
}

TObjectPtr<class UAnimMontage> AEKPlayerController::GetUnEquipAnimStaff()
{
	return StaffUnEquipAnim;
}