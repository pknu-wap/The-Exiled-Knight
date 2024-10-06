// Made by Somalia Pirate


#include "EKPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EKPlayer.h"

AEKPlayerController::AEKPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCDefaultFinder(TEXT("/Game/EKPlayer/Input/IMC_EK_Default"));
	if (IMCDefaultFinder.Succeeded())
	{
		IMCDefault = IMCDefaultFinder.Object;
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
	}
}

void AEKPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AEKPlayerController::MoveAction(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	FVector ForwardDirection = EKPlayer->GetActorForwardVector() * MovementVector.X;
	FVector RightDirection = EKPlayer->GetActorRightVector() * MovementVector.Y;

	EKPlayer->AddMovementInput(ForwardDirection, 1.f);
	EKPlayer->AddMovementInput(RightDirection, 1.f);
}

void AEKPlayerController::LookAction(const FInputActionValue& InputValue)
{
	FVector2D LookAxisVector = InputValue.Get<FVector2D>();

	EKPlayer->AddControllerYawInput(LookAxisVector.X);
	EKPlayer->AddControllerPitchInput(LookAxisVector.Y);
}

void AEKPlayerController::JumpAction(const FInputActionValue& InputValue)
{
	EKPlayer->Jump();
}