// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EKPlayer.generated.h"

UCLASS()
class AEKPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AEKPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UEKPlayerStatusComponent> PlayerStatusComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;
};
