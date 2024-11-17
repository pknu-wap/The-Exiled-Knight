// Made by Somalia Pirate


#include "AttackJump.h"
#include "../../EKPlayer/EKPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAttackJump::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp && MeshComp->GetOwner())
	{
		AActor* OwnerActor = MeshComp->GetOwner();

		EKPlayer = Cast<AEKPlayer>(OwnerActor);
		if (!EKPlayer)
		{
			return;
		}

		EKPlayer->GetCharacterMovement()->JumpZVelocity = 1200.f;
		EKPlayer->Jump();
		EKPlayer->GetCharacterMovement()->JumpZVelocity = 800.f;
	}
}