// Made by Somalia Pirate

#include "StaffTypeA.h"

AStaffTypeA::AStaffTypeA()
{
	PrimaryActorTick.bCanEverTick = true;

	Staff->SetStaticMesh(StaffMesh);

	WeaponAdditionalDamage = 5;
}

void AStaffTypeA::BeginPlay()
{
	Super::BeginPlay();

}

void AStaffTypeA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStaffTypeA::PlaySkillStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !StaffSkillAnim)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < StaffSkill ||
		EKPlayer->GetPlayerStatusComponent()->GetMp() < StaffSkillMp)
	{
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
		return;
	}

	EKPlayer->StopAnimMontage(StaffSkillAnim);
	EKPlayer->PlayAnimMontage(StaffSkillAnim, 1.0f, FName("Start"));
	EKPlayer->GetPlayerStatusComponent()->SetMp(-StaffSkillMp);
	EKPlayerController->ConsumtionStaminaAndTimer(StaffSkill);
	EKPlayerController->RemoveAttackTagTimer(StaffSkillAnim->GetPlayLength());
}