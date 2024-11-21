// Made by Somalia Pirate


#include "GreatSword.h"

AGreatSword::AGreatSword()
{
	PrimaryActorTick.bCanEverTick = true;

	GreatSword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GreatSword"));
	RootComponent = GreatSword;

	GreatSword->SetStaticMesh(GreatSwordMesh);

	WeaponCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	WeaponCapsuleComponent->SetupAttachment(RootComponent);
	WeaponCapsuleComponent->SetRelativeLocationAndRotation(FVector(60, 0, 0), FRotator(-90, 0, 0));
	WeaponCapsuleComponent->SetRelativeScale3D(FVector(1.f, 1.f, 3.f));

	MaxAttackCombo = 3;

	// Edit Weapon Default Damage Here
	WeaponAdditionalDamage = 20;
}

void AGreatSword::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGreatSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region Attack

void AGreatSword::PlayAttackStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !GreatSwordAttackAnim)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < GreatSwordAttackStamina)
	{
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
		return;
	}

	if (AttackCombo == 1)
	{
		EKPlayer->StopAnimMontage(GreatSwordAttackAnim);
		EKPlayer->PlayAnimMontage(GreatSwordAttackAnim, 1.0f, FName("Attack1"));
		EKPlayerController->SetAttackEndTimer(2.27f);
	}
	else if (AttackCombo == 2)
	{
		EKPlayer->StopAnimMontage(GreatSwordAttackAnim);
		EKPlayer->PlayAnimMontage(GreatSwordAttackAnim, 1.0f, FName("Attack2"));
		EKPlayerController->SetAttackEndTimer(2.37f);
	}
	else if (AttackCombo == 3)
	{
		EKPlayer->StopAnimMontage(GreatSwordAttackAnim);
		EKPlayer->PlayAnimMontage(GreatSwordAttackAnim, 1.0f, FName("Attack3"));
		EKPlayerController->SetAttackEndTimer(2.7f);
	}

	EKPlayerController->ConsumtionStaminaAndTimer(GreatSwordAttackStamina);
}

void AGreatSword::PlaySkillStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController)
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
	EKPlayer->PlayAnimMontage(GreatSwordSkillAnim);
	EKPlayer->GetPlayerStatusComponent()->SetMp(-GreatSwordSkillMp);
	EKPlayerController->ConsumtionStaminaAndTimer(GreatSwordSkill);
	EKPlayerController->RemoveAttackTagTimer(GreatSwordSkillAnim->GetPlayLength());
}

#pragma endregion

void AGreatSword::AttachToDefenseSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer)
{
	if (Weapon)
	{
		USkeletalMeshComponent* MeshComp = EKPlayer->GetMesh();
		if (MeshComp)
		{
			Weapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("greatsword_defense_socket"));
		}
	}
}