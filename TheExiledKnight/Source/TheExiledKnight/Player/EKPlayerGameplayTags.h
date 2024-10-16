// Made by Somalia Pirate

#pragma once

#include "NativeGameplayTags.h"

namespace EKPlayerGameplayTags
{
	// About EKPlayer Current State
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Idle);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Sprint);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Jump);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Attack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Dodge);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_BackStep);

	// About EKPlayer Attack
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_Attack_GreatSword_Combo1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_Attack_GreatSword_Combo2);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_Attack_GreatSword_Combo3);
}