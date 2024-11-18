// Made by Somalia Pirate

#include "GreatSwordTypeB.h"

AGreatSwordTypeB::AGreatSwordTypeB()
{
	PrimaryActorTick.bCanEverTick = true;

	// Edit Weapon Default Damage Here
	WeaponAdditionalDamage = 20;
}

void AGreatSwordTypeB::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGreatSwordTypeB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGreatSwordTypeB::PlaySkillStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !GreatSwordSkillAnim)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < GreatSwordSkill ||
		EKPlayer->GetPlayerStatusComponent()->GetMp() < GreatSwordSkillMp)
	{
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
		return;
	}

	EKPlayer->StopAnimMontage(GreatSwordSkillAnim);
	EKPlayer->PlayAnimMontage(GreatSwordSkillAnim, 1.0f, FName("Start"));
	EKPlayer->GetPlayerStatusComponent()->SetMp(-GreatSwordSkillMp);
	EKPlayerController->ConsumtionStaminaAndTimer(GreatSwordSkill);
}