// Made by Somalia Pirate


#include "EKPlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../EKPlayer/EKPlayer.h"

UEKPlayerAnimInstance::UEKPlayerAnimInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UEKPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EKPlayer = Cast<AEKPlayer>(GetOwningActor());
	if (EKPlayer)
	{
		EKMovementComponent = Cast<UCharacterMovementComponent>(EKPlayer->GetCharacterMovement());
	}
}

void UEKPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (EKPlayer == nullptr)
	{
		return;
	}
	if (EKMovementComponent == nullptr)
	{
		return;
	}

	Velocity = EKMovementComponent->Velocity;
	CurrentSpeed = Velocity.Size2D();
	bShouldMove = (CurrentSpeed > 3.f && EKMovementComponent->GetCurrentAcceleration() != FVector(0, 0, 0));
	bIsFalling = EKMovementComponent->IsFalling();
}