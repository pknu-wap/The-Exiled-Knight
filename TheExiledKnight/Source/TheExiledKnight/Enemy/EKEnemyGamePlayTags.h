// Made by Somalia Pirate
#pragma once
#include "NativeGameplayTags.h"  
namespace EKEnemyGameplayTags
{
	// About EKEnemy Current State
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKEnemy_State_None);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKEnemy_State_Investigating);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKEnemy_State_Combat);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKEnemy_State_Stunned); //when currentPoise is  zero
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKEnemy_State_Hurt); 
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKEnemy_State_Dead);



}