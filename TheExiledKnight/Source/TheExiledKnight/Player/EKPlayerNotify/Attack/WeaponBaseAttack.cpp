// Made by Somalia Pirate

#include "WeaponBaseAttack.h"
#include "../../EKPlayer/EKPlayer.h"
#include "../../EKPlayer/EKPlayerController.h"
#include "../../EKPlayerGameplayTags.h"
#include "../../Weapon/EKPlayerWeapon.h"
#include "../../../Enemy/EK_EnemyBase.h"
#include "../../Weapon/DamageType/EKPlayerDamageType.h"
#include "Subsystems/InventorySubsystem.h"

void UWeaponBaseAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	EKPlayer = Cast<AEKPlayer>(MeshComp->GetOwner());
	if (EKPlayer)
	{
		EKPlayerController = Cast<AEKPlayerController>(EKPlayer->GetController());
	}
}

void UWeaponBaseAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!EKPlayer || bIsHitOnce)
	{
		return;
	}

	UCapsuleComponent* WeaponCC = Cast<UCapsuleComponent>(EKPlayer->GetCurrentWeapon()->GetWeaponCapsuleComponent());

	if (!WeaponCC)
	{
		return;
	}

	FVector CapsuleLocation = WeaponCC->GetComponentLocation();
	FRotator CapsuleRotation = WeaponCC->GetComponentRotation();
	float CapsuleHalfHeight = WeaponCC->GetScaledCapsuleHalfHeight();
	float CapsuleRadius = WeaponCC->GetScaledCapsuleRadius();

	TArray<FHitResult> HitResults;

	// DrawDebugCapsule(GetWorld(), CapsuleLocation, CapsuleHalfHeight, CapsuleRadius, CapsuleRotation.Quaternion(), FColor::Red, false, 0.3f);

	bool bIsHit = MeshComp->GetWorld()->SweepMultiByChannel(
		HitResults,
		CapsuleLocation,
		CapsuleLocation,
		CapsuleRotation.Quaternion(),
		ECC_Pawn,
		FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight)
	);

	if (!bIsHit)
	{
		return;
	}

	for (auto& Hit : HitResults)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			TObjectPtr<AEK_EnemyBase> HitEnemy = Cast<AEK_EnemyBase>(HitActor);
			TSubclassOf<UEKPlayerDamageType> PlayerDamageType = UEKPlayerDamageType::StaticClass();
			if (HitEnemy)
			{
				EKPlayer->GetPlayerStatusComponent()->SetPlayerFinalDamage();
				USlotComponent* slotcomponent = EKPlayerController->GetSlotComponent();
				int activeWeaponSlot = slotcomponent->ActiveWeaponSlot;
				uint8 weaponID = slotcomponent->WeaponSlots[activeWeaponSlot].ID;
				FWeaponStruct* currentWeaponInfo = EKPlayerController->GetGameInstance()->GetSubsystem<UInventorySubsystem>()->GetWeaponInfo(weaponID);
				FLevelRate* currentWeaponLevel = EKPlayerController->GetGameInstance()->GetSubsystem<UInventorySubsystem>()->GetLevelRateInfo(slotcomponent->WeaponSlots[activeWeaponSlot].ItemLevel);
				
				float damageRateByWeaponType = 0.0f;
				
				if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_GreatSword))
				{
					damageRateByWeaponType = currentWeaponLevel->SwordRate;
				}
				else if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Spear))
				{
					damageRateByWeaponType = currentWeaponLevel->SpearRate;
				}
				else if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Staff))
				{
					damageRateByWeaponType = currentWeaponLevel->StaffRate;
				}

				float finalWeaponATK = currentWeaponInfo->AttackPow * damageRateByWeaponType;
				float finalPlayerATK = EKPlayer->GetPlayerStatusComponent()->GetPlayerFinalDamage();
				float finalApplyDamage = finalPlayerATK * finalWeaponATK;
				UGameplayStatics::ApplyDamage(HitEnemy, finalApplyDamage, EKPlayerController, EKPlayer->GetCurrentWeapon(), PlayerDamageType);
				UE_LOG(LogTemp, Warning, TEXT("ApplyDamge : %.2f"), finalApplyDamage);
				//UGameplayStatics::ApplyDamage(HitEnemy, EKPlayer->GetPlayerStatusComponent()->GetPlayerFinalDamage() * EKPlayer->GetCurrentWeapon()->DamageValue, EKPlayerController, EKPlayer->GetCurrentWeapon(), PlayerDamageType);
				bIsHitOnce = true;
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Attack!!!"));
			}
		}
	}
}

void UWeaponBaseAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!EKPlayerController || !EKPlayer)
	{
		return;
	}

	EKPlayerController->SetAttackComboNext();
	EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
	bIsHitOnce = false;
}