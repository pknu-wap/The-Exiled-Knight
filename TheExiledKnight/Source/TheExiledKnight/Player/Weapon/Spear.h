// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EKPlayerWeapon.h"
#include "Spear.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API ASpear : public AEKPlayerWeapon
{
	GENERATED_BODY()
	
public:	
	ASpear();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void PlayWeaponEquipAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) override;

	virtual void PlayAttackStartAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) override;

	virtual void PlayEnhancedAttackStartAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) override;

	virtual void PlayJumpAttackStartAnimMontage(TObjectPtr<class AEKPlayer> EKPlayer, TObjectPtr<class AEKPlayerController> EKPlayerController) override;

	virtual void AttachToDefenseSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<class AEKPlayer> EKPlayer) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class USkeletalMeshComponent> Spear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class USkeletalMesh> SpearMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class UCapsuleComponent> WeaponCapsuleComponent;

	virtual TObjectPtr<UCapsuleComponent> GetWeaponCapsuleComponent() override { return WeaponCapsuleComponent; }

protected:
	// Spear Animation Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> SpearAttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> SpearEquipAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> SpearUnEquipAnim;
};
