// Fill out your copyright notice in the Description page of Project Settings.


#include "EK_EnemyBase.h"
#include "EK_EnemyStatusComponent.h"
#include"Animation/AnimInstance.h"


// Sets default values
AEK_EnemyBase::AEK_EnemyBase()
{
	EnemyStat = CreateDefaultSubobject<UEK_EnemyStatusComponent>(TEXT("EnemyStat"));
}

float AEK_EnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInvestigator, AActor* DamageCauser)
{
	const float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInvestigator, DamageCauser);
	if (Damage > 0)
	{
		EnemyStat->ChangeCurrentHealth(Damage);
		EnemyStat->OnDamageTaken.Broadcast();
		FVector DamageDirection = (DamageCauser->GetActorLocation() - GetActorLocation()).GetSafeNormal(); 
		PlayHurtReactionAnimation(DamageDirection);
		if (EnemyStat->GetCurrentHealth() <= 0)
		{
			PlayDieReactionAnimation();
			EnemyStat->OnHPIsZero.Broadcast();
		}

	}
	return Damage;
}
TObjectPtr<UEK_EnemyStatusComponent> AEK_EnemyBase::GetStatusComponent()
{
	return EnemyStat;
}

#pragma region  PlayMontage

void AEK_EnemyBase::PlayHurtReactionAnimation(const FVector& DamageDirection)
{
	FVector Forward = GetActorForwardVector(); //forwar vector
	FVector Right = GetActorRightVector(); //right vector
	
	UAnimMontage* HurtMontage = nullptr;

	float  ForwardDot = FVector::DotProduct(Forward, DamageDirection);
	float RightDot = FVector::DotProduct(Right, DamageDirection);
		
	if (FMath::Abs(RightDot) > FMath::Abs(ForwardDot))
	{
		if (RightDot > 0)HurtMontage = hurtRMontage;
		else HurtMontage = hurtLMontage;
	}
	else
	{
		if (ForwardDot > 0)HurtMontage = hurtFMontage;
		else HurtMontage = hurtBMontage;
	}
	if (HurtMontage) 
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			// ANIMATION PLAY
			FOnMontageEnded MontageEndedDelegate;
			MontageEndedDelegate.BindUObject(this, &AEK_EnemyBase::OnHurtMontageEnded); 

			// ANIMATIONPLAY AND END DELEGATE ¼³Á¤
			AnimInstance->Montage_Play(HurtMontage);
			AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, HurtMontage);

		
		}
	}
}

void AEK_EnemyBase::OnHurtMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	OnHurtAnimationEnd.Broadcast(); 
}
void AEK_EnemyBase::PlayDieReactionAnimation()
{
	PlayAnimMontage(DeadMontage);  
}
#pragma endregion








