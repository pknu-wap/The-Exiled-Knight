// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "EKPlayer.generated.h"

UCLASS()
class AEKPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AEKPlayer();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	TObjectPtr<class AEKPlayerWeapon> GetCurrentWeapon();

	TObjectPtr<class UEKPlayerStatusComponent> GetPlayerStatusComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UEKPlayerStatusComponent> PlayerStatusComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;

public:
	void AttackHit();
	bool bIsHit = false;
	bool bIsHitOnce = false;

	void AttachWeaponToSpineSocket(TObjectPtr<class AEKPlayerWeapon> Weapon);
	void AttachWeaponToHandSocket(TObjectPtr<class AEKPlayerWeapon> Weapon);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AGreatSword> GreatSwordClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ASpear> SpearClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AStaff> StaffClass;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class AEKPlayerWeapon> CurrentWeapon;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationBlueprint")
	TSubclassOf<class UAnimInstance> ABPGreatSword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationBlueprint")
	TSubclassOf<class UAnimInstance> ABPSpear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationBlueprint")
	TSubclassOf<class UAnimInstance> ABPStaff;

public:
	UPROPERTY()
	FGameplayTagContainer EKPlayerStateContainer;
};
