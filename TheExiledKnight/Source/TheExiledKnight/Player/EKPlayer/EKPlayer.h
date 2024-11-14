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
	class AEKPlayerWeapon* GetCurrentWeapon() { return CurrentWeapon; }

	class UEKPlayerStatusComponent* GetPlayerStatusComponent() { return PlayerStatusComponent; }

	class UCapsuleComponent* GetLeftLegCapsuleComponent() { return LeftLegCapsuleComponent; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class AEKPlayerController> EKPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UEKPlayerStatusComponent> PlayerStatusComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule")
	TObjectPtr<class UCapsuleComponent> LeftLegCapsuleComponent;

public:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void HitDirection(AActor* Enemy);
	float HitAngle = 0.f;

	void AttachWeaponToSpineSocket(TObjectPtr<class AEKPlayerWeapon> Weapon);
	void AttachWeaponToHandSocket(TObjectPtr<class AEKPlayerWeapon> Weapon);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AGreatSwordTypeA> GreatSwordTypeAClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AGreatSwordTypeB> GreatSwordTypeBClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ASpearTypeA> SpearTypeAClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ASpearTypeB> SpearTypeBClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AStaffTypeA> StaffTypeAClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AStaffTypeB> StaffTypeBClass;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<class AEKPlayerWeapon> CurrentWeapon;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationBlueprint")
	TSubclassOf<class UAnimInstance> ABPEKPlayer;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTagContainer EKPlayerStateContainer;

protected:
	FTimerHandle HitTagHandle;

	const float NextHitTime = 0.5f;

	void RemoveHitTag();
	void HitTimer();
};
