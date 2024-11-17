// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EKFireMagicSpellNotify.generated.h"

/**
 * 
 */
UCLASS()
class THEEXILEDKNIGHT_API UEKFireMagicSpellNotify : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override; 

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MagicSpell", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEKEnemyProjectileBase> MagicSpell;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MagicSpell", meta = (AllowPrivateAccess = "true"))
	FName SocketName; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MagicSpell", meta = (AllowPrivateAccess = "true"))
	float  DamagePercent=1.0f;
};
