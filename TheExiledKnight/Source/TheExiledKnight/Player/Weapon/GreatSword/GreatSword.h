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
	virtual void PlayAttackStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController) override;

	virtual void AttachToDefenseSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer) override;

	virtual void PlaySkillStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* GreatSword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UStaticMesh* GreatSwordMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UCapsuleComponent* WeaponCapsuleComponent;

	virtual UCapsuleComponent* GetWeaponCapsuleComponent() override { return WeaponCapsuleComponent; }

protected:
	// GreatSword Animation Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* GreatSwordAttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* GreatSwordSkillAnim;
};
