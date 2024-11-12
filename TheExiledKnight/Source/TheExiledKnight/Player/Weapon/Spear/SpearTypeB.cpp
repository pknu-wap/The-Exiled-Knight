// Made by Somalia Pirate

#include "SpearTypeB.h"

ASpearTypeB::ASpearTypeB()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponAdditionalDamage = 10;
}

void ASpearTypeB::BeginPlay()
{
	Super::BeginPlay();

}

void ASpearTypeB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpearTypeB::PlaySkillStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !SpearSkillAnim)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < SpearSkill ||
		EKPlayer->GetPlayerStatusComponent()->GetMp() < SpearSkillMp)
	{
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
		return;
	}

	EKPlayer->StopAnimMontage(SpearSkillAnim);
	EKPlayer->PlayAnimMontage(SpearSkillAnim, 1.0f, FName("Start"));
	EKPlayer->GetPlayerStatusComponent()->SetMp(-SpearSkillMp);
	EKPlayerController->ConsumtionStaminaAndTimer(SpearSkill);
}