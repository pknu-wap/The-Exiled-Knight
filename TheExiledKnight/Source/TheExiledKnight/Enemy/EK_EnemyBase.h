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
	
	void OnHurtAnimationEnded(UAnimMontage* Montage, bool bInterrupted);

	void OnDeathAnimationEnded(UAnimMontage* Montage, bool bInterrupted);

	void PlayDieReactionAnimation();
	
	float GetSightRadius();

	float GetLostSightRadius();

	float GetHearingRange();

	AActor *GetAttackTarget();
	
	UFUNCTION(BlueprintCallable) 
	void SetAttackTarget(AActor* Actor);
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* AttackAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* hurtFAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* hurtLAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* hurtRAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* hurtBAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* DeathAnimMontage;


public:	
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UEK_EnemyStatusComponent* EnemyStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree");
	UBehaviorTree* BehaviorTree;
	
	virtual TObjectPtr <UEK_EnemyStatusComponent> GetStatusComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception", meta = (AllowPrivateAccess = "true"))
	float SightRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception", meta = (AllowPrivateAccess = "true"))
	float LostSightRadius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception", meta = (AllowPrivateAccess = "true"))
	float HearingRange = 2000.0f;

	UPROPERTY()
	AActor* AttackTarget;
	
};
