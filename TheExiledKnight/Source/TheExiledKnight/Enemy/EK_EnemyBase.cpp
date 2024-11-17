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
	if (DamageCauser)
	{
		SetAttackTarget(DamageCauser);
	}

	if (EnemyStat->GetCurrentHealth() > 0&&!bIsDead) 
	{
		if (Damage > 0)
		{
			EnemyStat->DamageCurrentHealth(Damage);

			FVector DamageDirection = (DamageCauser->GetActorLocation() - GetActorLocation()).GetSafeNormal();
			PlayHurtReactionAnimation(DamageDirection);
			if (EnemyStat->GetCurrentHealth() <= 0)
			{
				bIsDead = true;
				PlayDieReactionAnimation();
				EnemyStat->OnHPIsZero.Broadcast();
			}

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
		if (RightDot > 0)HurtMontage = hurtRAnimMontage;
		else HurtMontage = hurtLAnimMontage;
	}
	else
	{
		if (ForwardDot > 0)HurtMontage = hurtFAnimMontage;
		else HurtMontage = hurtBAnimMontage;
	}
	EnemyStat->OnDamageTaken.Broadcast();  
	if (HurtMontage) 
	{
		 
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{

			FOnMontageEnded MontageEndedDelegate;
			MontageEndedDelegate.BindUObject(this, &AEK_EnemyBase::OnHurtAnimationEnded);
			AnimInstance->Montage_Play(HurtMontage); 
			AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, HurtMontage);
		
		}
	}
			
}

void AEK_EnemyBase::OnHurtAnimationEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
	{	
		UE_LOG(LogTemp, Warning, TEXT("OnHurtAnimationEnded called"));
		OnHurtAnimationEnd.Broadcast();
	}
}

void AEK_EnemyBase::PlayDieReactionAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); 
	if (AnimInstance && DeathAnimMontage)
	{
		
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &AEK_EnemyBase::OnDeathAnimationEnded);
		AnimInstance->Montage_Play(DeathAnimMontage);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, DeathAnimMontage);
	}
}
void AEK_EnemyBase::OnDeathAnimationEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
	{
		for (AActor* Actor : AttachedActors)
		{
			if (Actor)
			{
				Actor->Destroy();
			}
		}
		Destroy();
	}
}

float AEK_EnemyBase::GetSightRadius()
{
	return SightRadius;
}

float AEK_EnemyBase::GetLostSightRadius()
{
	return LostSightRadius;
}

float AEK_EnemyBase::GetHearingRange()
{
	return HearingRange;
}

AActor* AEK_EnemyBase::GetAttackTarget()
{
	return AttackTarget;
}

void AEK_EnemyBase::SetAttackTarget(AActor* Actor)
{
	if (Actor)
	{
		AttackTarget = Actor;
	}
}

#pragma endregion








