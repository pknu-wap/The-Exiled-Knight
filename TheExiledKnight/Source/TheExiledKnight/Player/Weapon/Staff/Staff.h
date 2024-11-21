// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "../EKPlayerWeapon.h"
#include "Staff.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AStaff : public AEKPlayerWeapon
{
	GENERATED_BODY()
	
public:
	AStaff();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void PlayAttackStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController) override;

	virtual void AttachToDefenseSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer) override;

	virtual void AttachWeaponToSpineSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer) override;
	virtual void AttachWeaponToHandSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer) override;

	virtual void PlaySkillStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* Staff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UStaticMesh* StaffMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UCapsuleComponent* WeaponCapsuleComponent;

	virtual UCapsuleComponent* GetWeaponCapsuleComponent() override { return WeaponCapsuleComponent; }

protected:
	// Staff Animation Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* StaffAttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* StaffAttackMagicAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* StaffSkillAnim;
};