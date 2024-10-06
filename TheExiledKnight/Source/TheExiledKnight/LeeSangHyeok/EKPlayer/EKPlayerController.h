// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EKPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class AEKPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AEKPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	void MoveAction(const FInputActionValue& InputValue);
	void LookAction(const FInputActionValue& InputValue);
	void JumpAction(const FInputActionValue& InputValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> IMCDefault;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IAMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IALook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IAJump;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AEKPlayer> EKPlayer;
};
