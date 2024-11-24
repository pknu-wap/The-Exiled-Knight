// Made by Somalia Pirate

#pragma once

#include "NativeGameplayTags.h"

namespace EKPlayerGameplayTags
{
	// About EKPlayer Current State
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_BattleState);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_DomainExpansion);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Look);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Sprint);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Jump);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Attack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Defense);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Dodge);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_UseItem);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_SitDown);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Hit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_StrongHit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Invincibility);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_State_Die);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_Equip_GreatSword);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_Equip_Spear);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EKPlayer_Equip_Staff);
}