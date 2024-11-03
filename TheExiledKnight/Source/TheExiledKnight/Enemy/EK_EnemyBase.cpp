// Fill out your copyright notice in the Description page of Project Settings.


#include "EK_EnemyBase.h"
#include "EK_EnemyStatusComponent.h"

// Sets default values
AEK_EnemyBase::AEK_EnemyBase()
{
	EnemyStat = CreateDefaultSubobject<UEK_EnemyStatusComponent>(TEXT("EnemyStat"));
}

float AEK_EnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInvestigator, AActor* DmageCauser)
{
	const float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInvestigator, DmageCauser);
	if (Damage > 0)
	{
		EnemyStat->ChangeCurrentHealth(Damage);
		EnemyStat->OnDamageTaken.Broadcast();
		if (EnemyStat->GetCurrentHealth() <= 0)
		{
			EnemyStat->OnHPIsZero.Broadcast();
		}


	}
	return 0.0f;
}


TObjectPtr<UEK_EnemyStatusComponent> AEK_EnemyBase::GetStatusComponent()
{
	return EnemyStat;
}








