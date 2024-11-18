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
	virtual void PlayWeaponEquipAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController) override;

	virtual void PlayAttackStartAnimMontage(AEKPlayer* EKPlayer, AEKPlayerController* EKPlayerController) override;

	virtual void AttachToDefenseSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer) override;

	virtual void AttachWeaponToSpineSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer) override;
	virtual void AttachWeaponToHandSocket(AEKPlayerWeapon* Weapon, AEKPlayer* EKPlayer) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class UStaticMeshComponent> Staff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class UStaticMesh> StaffMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class UCapsuleComponent> WeaponCapsuleComponent;

	virtual TObjectPtr<UCapsuleComponent> GetWeaponCapsuleComponent() override { return WeaponCapsuleComponent; }

protected:
	// Staff Animation Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> StaffAttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> StaffAttackMagicAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> StaffEquipAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> StaffUnEquipAnim;

protected:
	bool bIsFirstAttackMagic = true;
};