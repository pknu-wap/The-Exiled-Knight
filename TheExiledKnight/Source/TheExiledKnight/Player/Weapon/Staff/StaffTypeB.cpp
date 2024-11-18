// Made by Somalia Pirate

#include "StaffTypeB.h"

AStaffTypeB::AStaffTypeB()
{
	PrimaryActorTick.bCanEverTick = true;

	Staff->SetStaticMesh(StaffMesh);

	WeaponAdditionalDamage = 5;
}

void AStaffTypeB::BeginPlay()
{
	Super::BeginPlay();

}

void AStaffTypeB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStaffTypeB::PlaySkillStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController)
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
	EKPlayerController->RemoveAttackTagTimer(2.5f);
}