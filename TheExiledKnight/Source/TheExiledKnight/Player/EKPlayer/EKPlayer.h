// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Enum/EKPlayerBehaviorState.h"
#include "../Enum/EKPlayerEquipWeapon.h"
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
	EEKPlayerBehaviorState GetPlayerCurrentState();
	void SetPlayerCurrentState(EEKPlayerBehaviorState Change);

	EEKPlayerEquipWeapon GetPlayerCurrentWeapon();
	void SetPlayerCurrentWeapon(EEKPlayerEquipWeapon Change);

	TObjectPtr<class AEKPlayerWeapon> GetCurrentWeapon();

	void OnDamaged();
	void OnDead();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EEKPlayerBehaviorState PlayerCurrentState = EEKPlayerBehaviorState::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EEKPlayerEquipWeapon PlayerCurrentWeapon = EEKPlayerEquipWeapon::None;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UEKPlayerStatusComponent> PlayerStatusComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;

public:
	void AttachGreatSwordToEquipSocket(TObjectPtr<class AEKPlayerWeapon> Weapon);
	void AttachGreatSwordToHandSocket(TObjectPtr<class AEKPlayerWeapon> Weapon);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AGreatSword> GreatSwordClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ASpear> SpearClass;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class AEKPlayerWeapon> CurrentWeapon;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationBlueprint")
	TSubclassOf<class UAnimInstance> ABPGreatSword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationBlueprint")
	TSubclassOf<class UAnimInstance> ABPSpear;
};
