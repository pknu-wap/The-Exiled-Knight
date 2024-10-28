// Made by Somalia Pirate


#include "Spear.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "../EKPlayer/EKPlayer.h"
#include "../EKPlayer/EKPlayerController.h"
#include "../EKPlayer/EKPlayerStatusComponent.h"

ASpear::ASpear()
{
	PrimaryActorTick.bCanEverTick = true;

	Spear = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Spear"));
	RootComponent = Spear;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SpearMeshFinder(TEXT("/AssetShare/Animations/Frank_Spear/Mesh/Frank_UE_Spear_Weapon_Skin"));
	if (SpearMeshFinder.Succeeded())
	{
		SpearMesh = SpearMeshFinder.Object;
	}
	Spear->SetSkeletalMesh(SpearMesh);
}

void ASpear::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpear::PlayWeaponEquipAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (EKPlayer && EKPlayerController)
	{
		if (!EKPlayerController->bIsEquipWeapon && EKPlayerController->GetEquipAnimSpear())
		{
			EKPlayer->PlayAnimMontage(EKPlayerController->GetEquipAnimSpear());
		}
		else if (EKPlayerController->bIsEquipWeapon && EKPlayerController->GetUnEquipAnimSpear())
		{
			EKPlayer->PlayAnimMontage(EKPlayerController->GetUnEquipAnimSpear());
		}
	}
}

void ASpear::PlayAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayerController->bIsEquipWeapon || !EKPlayerController->GetSpearAttackAnim())
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < SpearAttackStamina)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 1)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearAttackAnim(), 1.0f, FName("Attack1"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 2 && EKPlayerController->bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearAttackAnim(), 1.0f, FName("Attack2"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 3 && EKPlayerController->bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearAttackAnim(), 1.0f, FName("Attack3"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 4 && EKPlayerController->bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearAttackAnim(), 1.0f, FName("Attack4"));
	}
	else if (EKPlayer->GetPlayerStatusComponent()->GetSpearCombo() == 5 && EKPlayerController->bCanAttackNext == true)
	{
		EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearAttackAnim(), 1.0f, FName("Attack5"));
	}

	EKPlayerController->SetStaminaAndTimer(SpearAttackStamina);
}

void ASpear::PlayDefenseStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearDefenseAnim(), 1.f, FName("Start"));
}

void ASpear::PlayDefenseTriggerAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearDefenseAnim(), 1.f, FName("Loop"));
}

void ASpear::PlayDefenseReleaseAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController)
{
	if (!EKPlayer || !EKPlayerController)
	{
		return;
	}

	EKPlayer->PlayAnimMontage(EKPlayerController->GetSpearDefenseAnim(), 1.f, FName("End"));
}

void ASpear::AttachWeaponToSpineSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
{
	Super::AttachWeaponToSpineSocket(Weapon, EKPlayer);
}

void ASpear::AttachWeaponToHandSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer)
{
	Super::AttachWeaponToHandSocket(Weapon, EKPlayer);
}