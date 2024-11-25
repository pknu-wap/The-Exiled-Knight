// Fill out your copyright notice in the Description page of Project Settings.


#include "EK_EnemyBase.h"
#include "EK_EnemyStatusComponent.h"
#include"Player/Weapon/DamageType/EKPlayerDamageType.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include"Animation/AnimInstance.h"
#include"Enemy/DamageSystem/EKDamageType.h"
#include"Player/EKPlayer/EKPlayer.h"
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
	

	if (EnemyStat->GetCurrentHealth() > 0 && !EnemyStat->GetIsDead())
	{
		if (Damage > 0)
		{
			
			if (DamageTypeClass->IsChildOf(UEKStrongDamageType::StaticClass()))
			{
				HandleStrongAttack(Damage);
			}
			else
			{
				HandleNormalAttack(Damage);
			}

			
			if (EnemyStat->GetCurrentHealth() <= 0)
			{
				EnemyStat->SetIsDead(true);
				PlayDieReactionAnimation();
				EnemyStat->OnHPIsZero.Broadcast();
				return 0.0f;
			}

			// 피격 애니메이션 재생
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
		EnemyStat->DamageCurrentPoise(Damage*0.2f);
		
	}
}
void AEK_EnemyBase::HandleNormalAttack(float Damage)
{
	EnemyStat->DamageCurrentHealth(Damage); 

	if (EnemyStat->GetCurrentPoise() > 0)
	{
		EnemyStat->DamageCurrentPoise(Damage*0.1f);
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

	 
	if (HurtMontage) 
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance&&BeforeHurtMontage==nullptr)
		{
			if (AnimInstance->IsAnyMontagePlaying())AnimInstance->StopAllMontages(0.1f);  
			EnemyStat->OnDamageTaken.Broadcast();  
			FOnMontageEnded MontageEndedDelegate;
			MontageEndedDelegate.BindUObject(this, &AEK_EnemyBase::OnHurtAnimationEnded);
			AnimInstance->Montage_Play(HurtMontage); 
			BeforeHurtMontage = HurtMontage;
			AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, HurtMontage);
		
		}
	}
	else //don't have hurt montage 
	{
		EnemyStat->OnDamageTaken.Broadcast();
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
		bIsStunned = false;
		if (AnimInstance->Montage_IsPlaying(StunMontage))
		{
			AnimInstance->Montage_Stop(0.1f,StunMontage);
		}
	
		AnimInstance->StopAllMontages(0.1f);
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &AEK_EnemyBase::OnDeathAnimationEnded);
		AnimInstance->Montage_Play(DeathAnimMontage, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, true);
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











