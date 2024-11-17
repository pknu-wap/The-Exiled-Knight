// Made by Somalia Pirate

#include "GreatSwordTypeA.h"

AGreatSwordTypeA::AGreatSwordTypeA()
{
	PrimaryActorTick.bCanEverTick = true;

	// Edit Weapon Default Damage Here
	WeaponAdditionalDamage = 20;

	DamageValue = 1.f;
}

void AGreatSwordTypeA::BeginPlay()
{
	Super::BeginPlay();

}

void AGreatSwordTypeA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGreatSwordTypeA::PlaySkillStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController)
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