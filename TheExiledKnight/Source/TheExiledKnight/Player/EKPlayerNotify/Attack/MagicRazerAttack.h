// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "Player/EKPlayer/EKPlayer.h"
#include "MagicRazerAttack.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API UMagicRazerAttack : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	AEKPlayer* EKPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEKPlayerProjectile> RazerPro;
};