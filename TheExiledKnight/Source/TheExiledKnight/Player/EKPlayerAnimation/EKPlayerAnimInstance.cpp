// Made by Somalia Pirate


#include "EKPlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../EKPlayer/EKPlayer.h"
#include "../EKPlayer/EKPlayerController.h"
#include "../EKPlayer/EKPlayerStatusComponent.h"
#include "../EKPlayerGameplayTags.h"

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
		EKPlayerController = Cast<AEKPlayerController>(EKPlayer->GetController());
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
	HitAngle = EKPlayer->HitAngle;

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_SitDown))
	{
		bIsSitted = true;
	}
	else
	{
		bIsSitted = false;
	}

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Hit))
	{
		bIsHitted = true;
	}
	else
	{
		bIsHitted = false;
	}

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Defense))
	{
		bIsDefense = true;
	}
	else
	{
		bIsDefense = false;
	}

	Stamina = EKPlayer->GetPlayerStatusComponent()->GetStamina();
}