// Fill out your copyright notice in the Description page of Project Settings.


#include "EKEnemyGamePlayTags.h"
namespace EKEnemyGameplayTags
{
#pragma region State

	UE_DEFINE_GAMEPLAY_TAG(EKEnemy_State_None, "EKEnemy.State.Idle"); //patrol or  idle
	UE_DEFINE_GAMEPLAY_TAG(EKEnemy_State_Investigating, "EKEnemy.State.Investigating");
	UE_DEFINE_GAMEPLAY_TAG(EKEnemy_State_Combat, "EKEnemy.State.Combat");
	UE_DEFINE_GAMEPLAY_TAG(EKEnemy_State_Stunned, "EKEnemy.State.Stunned");
	UE_DEFINE_GAMEPLAY_TAG(EKEnemy_State_Hurt, "EKEnemy.State.Hurt");
	UE_DEFINE_GAMEPLAY_TAG(EKEnemy_State_Dead, "EKEnemy.State.Dead");
#pragma endregion



}