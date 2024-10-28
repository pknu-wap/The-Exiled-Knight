// Made by Somalia Pirate
#pragma once
#include "NativeGameplayTags.h"  
namespace EKEnemyGameplayTags
{
	// About EKEnemy Current State
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKEnemy_State_Idle);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKEnemy_State_Walk);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKEnemy_State_Sprint);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKEnemy_State_Attack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKEnemy_State_Chase);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKEnemy_State_Stun); //when currentPoise is  zero


}