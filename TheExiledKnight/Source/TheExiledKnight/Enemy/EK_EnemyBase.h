// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EK_EnemyBase.generated.h"

 

UCLASS()
class THEEXILEDKNIGHT_API AEK_EnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEK_EnemyBase(); 

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInvestigator, AActor* DamageCauser)override;
	
	void PlayHurtReactionAnimation(const FVector& DamageDirection);   
	
	void OnHurtAnimationEnded(UAnimMontage* Montage, bool bInterrupted);

	void PlayDieReactionAnimation(); 

	void OnDeathAnimationEnded(UAnimMontage* Montage, bool bInterrupted);

	void PlayStunReactionAnimation();

	void OnStunAnimationEnded(UAnimMontage* Montage, bool bInterrupted);

	void HandleStrongAttack(float Damage);

	void HandleNormalAttack(float Damage);

	
	UFUNCTION(BlueprintCallable)
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"));
	UAnimMontage* StunMontage;
public:	
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UEK_EnemyStatusComponent* EnemyStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree");
	UBehaviorTree* BehaviorTree;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> AttachedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception", meta = (AllowPrivateAccess = "true"))
	AActor* AttackTarget;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bIsStunned = false;
	
	virtual TObjectPtr <UEK_EnemyStatusComponent> GetStatusComponent(); 

	UAnimMontage* BeforeHurtMontage = nullptr;
	
	// Related to Sanctuary (Map)
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int SantuaryID = 0;
};
