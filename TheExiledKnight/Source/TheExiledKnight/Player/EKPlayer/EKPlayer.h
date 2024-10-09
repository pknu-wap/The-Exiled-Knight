// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../EKPlayerBehaviorState.h"
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

	void OnDamaged();
	void OnDead();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EEKPlayerBehaviorState PlayerCurrentState = EEKPlayerBehaviorState::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UEKPlayerStatusComponent> PlayerStatusComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;

public:
	void AttachGreatSwordToSocket(TObjectPtr<class AGreatSword> Weapon);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AGreatSword> GreatSwordClass;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AGreatSword> CurrentWeapon;
};
