// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Player/Weapon/Projectile/EKPlayerProjectile.h"
#include "Player/EKPlayer/EKPlayer.h"
#include "Player/Weapon/Projectile/ThunderingProjectile.h"
#include "ThunderingAttack.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API UThunderingAttack : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	AEKPlayer* EKPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEKPlayerProjectile> Thundering1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEKPlayerProjectile> Thundering2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEKPlayerProjectile> Thundering3;
	
	uint8 SummonTunder = 0;
	float ThunderLocation = 250.f;

	FTimerHandle TunderSummonHandle;

	void SummonTundering();
	void SummonTunderingTimer();
};	 