// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EK_EnemyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHitAnimationEnd);   

UCLASS()
class THEEXILEDKNIGHT_API AEK_EnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEK_EnemyBase(); 

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInvestigator, AActor* DamageCauser)override;
	
	UPROPERTY(BlueprintAssignable, Category = "HitAnimation")
	FOnHitAnimationEnd OnHurtAnimationEnd;  

	void PlayHurtReactionAnimation(const FVector& DamageDirection);
	void OnHurtMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void PlayDieReactionAnimation();
	

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* hurtFMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* hurtLMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* hurtRMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* hurtBMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* DeadMontage;


public:	
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UEK_EnemyStatusComponent* EnemyStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree");
	UBehaviorTree* BehaviorTree;
	
	virtual TObjectPtr <UEK_EnemyStatusComponent> GetStatusComponent();
	

	
};
