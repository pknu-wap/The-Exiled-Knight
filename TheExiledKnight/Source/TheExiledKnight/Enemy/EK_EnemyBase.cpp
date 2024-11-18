// Fill out your copyright notice in the Description page of Project Settings.


#include "EK_EnemyBase.h"
#include "EK_EnemyStatusComponent.h"
#include"Player/Weapon/DamageType/EKPlayerDamageType.h"
#include "Engine/DamageEvents.h"
#include"Animation/AnimInstance.h"
#include"Enemy/DamageSystem/EKDamageType.h"
#include"Enemy/EKEnemyGamePlayTags.h"



// Sets default values
AEK_EnemyBase::AEK_EnemyBase()
{
	EnemyStat = CreateDefaultSubobject<UEK_EnemyStatusComponent>(TEXT("EnemyStat"));
}
#pragma region DamageSystem

float AEK_EnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInvestigator, AActor* DamageCauser)
{
	const float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInvestigator, DamageCauser);

	TSubclassOf<UDamageType> DamageTypeClass = DamageEvent.DamageTypeClass;

	if (DamageCauser)
	{
		SetAttackTarget(DamageCauser);
	}
	

	if (EnemyStat->GetCurrentHealth() > 0&&!EnemyStat->GetIsDead()) 
	{
		if (Damage > 0)
		{
			
			if (DamageTypeClass->IsChildOf(UEKStrongDamageType::StaticClass()))
			{
				HandleStrongAttack(Damage);
			}
			else if (DamageTypeClass->IsChildOf(UEKNormalDamageType::StaticClass()))
			{
				HandleNormalAttack(Damage);
			}
			else
			{
				HandleNormalAttack(Damage); //before merge i use 
			}
			
			if (EnemyStat->GetCurrentHealth() <= 0)
			{
				EnemyStat->SetIsDead(true);
				PlayDieReactionAnimation();
				EnemyStat->OnHPIsZero.Broadcast();
				return 0.0f;
			}

				FVector DamageDirection = (DamageCauser->GetActorLocation() - GetActorLocation()).GetSafeNormal();
				PlayHurtReactionAnimation(DamageDirection);
		}
	}
	return Damage;
}
#pragma endregion
#pragma region HanadleDamageType
void AEK_EnemyBase::HandleStrongAttack(float Damage)
{
	EnemyStat->DamageCurrentHealth(Damage*1.2f);
	if (EnemyStat->GetCurrentPoise() > 0)
	{
		EnemyStat->DamageCurrentPoise(50);
		
	}
}
void AEK_EnemyBase::HandleNormalAttack(float Damage)
{
	EnemyStat->DamageCurrentHealth(Damage); 
	if (EnemyStat->GetCurrentPoise() > 0)
	{
		EnemyStat->DamageCurrentPoise(50);
	}
}

#pragma endregion

#pragma region  PlayHurtMontage

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
		if (AnimInstance->Montage_IsPlaying(StunMontage))StopAnimMontage(StunMontage);
		if (AnimInstance&&BeforeHurtMontage==nullptr)
		{
			FOnMontageEnded MontageEndedDelegate;
			MontageEndedDelegate.BindUObject(this, &AEK_EnemyBase::OnHurtAnimationEnded);
			AnimInstance->Montage_Play(HurtMontage); 
			BeforeHurtMontage = HurtMontage;
			AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, HurtMontage);
		
		}
		
	}
			
}

void AEK_EnemyBase::OnHurtAnimationEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
	{	
		UE_LOG(LogTemp, Warning, TEXT("OnHurtAnimationEnded called"));
		EnemyStat->OnHurtAnimationEnd.Broadcast();
		BeforeHurtMontage = nullptr;
	}
	if (EnemyStat->GetCurrentPoise() <= 0 && !bIsStunned) //stun animation montage 
	{
		bIsStunned = true;
		PlayStunReactionAnimation();

	}
}

#pragma endregion
#pragma region PlayDieMontage

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
#pragma endregion
#pragma region PlayStunMontage
void AEK_EnemyBase::PlayStunReactionAnimation() //just one time so I use Enemy_State_Stunned 
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); 
	if (AnimInstance && StunMontage)
	{
	
		EnemyStat->OnPoiseIsZero.Broadcast();
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &AEK_EnemyBase::OnStunAnimationEnded);
		AnimInstance->Montage_Play(StunMontage);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, StunMontage);
	}
}
void AEK_EnemyBase::OnStunAnimationEnded(UAnimMontage* Montage, bool bInterrupted)
{
	EnemyStat->ResetCurrentPoise();
	EnemyStat->OnStunAnimationEnd.Broadcast();
	bIsStunned = false;
}
#pragma endregion




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
TObjectPtr<UEK_EnemyStatusComponent> AEK_EnemyBase::GetStatusComponent() 
{
	return EnemyStat;
}

void AEK_EnemyBase::SetAttackTarget(AActor* Actor)
{
	if (Actor)
	{
		AttackTarget = Actor;
	}
}










