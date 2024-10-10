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
#include "GameFramework/CharacterMovementComponent.h"

AEKPlayerController::AEKPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCGreatSwordFinder(TEXT("/Game/EKPlayer/Input/GreatSword/IMC_EK_GreatSword"));
	if (IMCGreatSwordFinder.Succeeded())
	{
		IMCDefault = IMCGreatSwordFinder.Object;
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

	ConstructorHelpers::FObjectFinder<UInputAction> IAGreatSwordAttackFinder(TEXT("/Game/EKPlayer/Input/GreatSword/IA_EK_GreatSword_Attack"));
	if (IAGreatSwordAttackFinder.Succeeded())
	{
		IAGreatSwordAttack = IAGreatSwordAttackFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> GreatSwordAttackAnimFinder(TEXT("/Game/EKPlayer/Animation/GreatSword/GreatSwordAttack/EKPlayer_Combo1"));
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
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &ThisClass::MoveAction);
		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Triggered, this, &ThisClass::LookAction);
		EnhancedInputComponent->BindAction(IAJump, ETriggerEvent::Triggered, this, &ThisClass::JumpAction);

		EnhancedInputComponent->BindAction(IAWeaponChange, ETriggerEvent::Triggered, this, &ThisClass::WeaponChangeAction);

		//EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Started, this, &ThisClass::SprintAndDodgeAction);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Triggered, this, &ThisClass::SprintAndDodgeAction);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Completed, this, &ThisClass::SprintAndDodgeRelease);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Canceled, this, &ThisClass::SprintAndDodgeRelease);

		EnhancedInputComponent->BindAction(IAGreatSwordAttack, ETriggerEvent::Triggered, this, &ThisClass::GreatSwordAttackAction);
	}
}

void AEKPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	/*if (EKPlayer->GetPlayerCurrentState() == EEKPlayerBehaviorState::Jump && !EKPlayer->GetMovementComponent()->IsFalling())
	{
		EKPlayer->SetPlayerCurrentState(EEKPlayerBehaviorState::Idle);
	}*/
}

void AEKPlayerController::MoveAction(const FInputActionValue& InputValue)
{
	/*if (EKPlayer->GetPlayerCurrentState() == EEKPlayerBehaviorState::Attack)
	{
		return;
	}*/

	FVector2D MovementVector = InputValue.Get<FVector2D>();

	if (MovementVector.X != 0 || MovementVector.Y != 0)
	{
		//EKPlayer->SetPlayerCurrentState(EEKPlayerBehaviorState::Move);

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
	else
	{
		//EKPlayer->SetPlayerCurrentState(EEKPlayerBehaviorState::Idle);
	}
}

void AEKPlayerController::LookAction(const FInputActionValue& InputValue)
{
	FVector2D LookAxisVector = InputValue.Get<FVector2D>();

	EKPlayer->AddControllerYawInput(LookAxisVector.X);
	EKPlayer->AddControllerPitchInput(LookAxisVector.Y);
}

void AEKPlayerController::JumpAction(const FInputActionValue& InputValue)
{
	/*if (EKPlayer->GetPlayerCurrentState() == EEKPlayerBehaviorState::Attack)
	{
		return;
	}

	EKPlayer->SetPlayerCurrentState(EEKPlayerBehaviorState::Jump);*/

	EKPlayer->Jump();
}

void AEKPlayerController::WeaponChangeAction(const FInputActionValue& InputValue)
{
	if (!bIsEquipGreatSword && GreatSwordEquipAnim)
	{
		EKPlayer->PlayAnimMontage(GreatSwordEquipAnim);
		bIsEquipGreatSword = true;
	}
	else if (bIsEquipGreatSword && GreatSwordUnEquipAnim)
	{
		EKPlayer->PlayAnimMontage(GreatSwordUnEquipAnim);
		bIsEquipGreatSword = false;
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
		EKPlayer->GetCharacterMovement()->MaxWalkSpeed = 300;
	}
}

void AEKPlayerController::GreatSwordAttackAction(const FInputActionValue& InputValue)
{
	/*if (EKPlayer->GetPlayerCurrentState() != EEKPlayerBehaviorState::Idle)
	{
		return;
	}

	EKPlayer->SetPlayerCurrentState(EEKPlayerBehaviorState::Attack);*/

	if (!bIsEquipGreatSword)
	{
		return;
	}

	if (GreatSwordAttackAnim)
	{
		EKPlayer->PlayAnimMontage(GreatSwordAttackAnim);
	}
}