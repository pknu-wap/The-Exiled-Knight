// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "../EKPlayerWeapon.h"
#include "GreatSword.generated.h"

class UAnimMontage;

UCLASS()
class THEEXILEDKNIGHT_API AGreatSword : public AEKPlayerWeapon
{
	GENERATED_BODY()
	
public:	
	AGreatSword();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void PlayWeaponEquipAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController) override;

	virtual void PlayAttackStartAnimMontage(TObjectPtr<AEKPlayer> EKPlayer, TObjectPtr<AEKPlayerController> EKPlayerController) override;

	virtual void AttachToDefenseSocket(TObjectPtr<AEKPlayerWeapon> Weapon, TObjectPtr<AEKPlayer> EKPlayer) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class UStaticMeshComponent> GreatSword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class UStaticMesh> GreatSwordMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<UCapsuleComponent> WeaponCapsuleComponent;

	virtual TObjectPtr<UCapsuleComponent> GetWeaponCapsuleComponent() override { return WeaponCapsuleComponent; }

protected:
	// GreatSword Animation Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> GreatSwordAttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> GreatSwordEquipAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> GreatSwordUnEquipAnim;
};
