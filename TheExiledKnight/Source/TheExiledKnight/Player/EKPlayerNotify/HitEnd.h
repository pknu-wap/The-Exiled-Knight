// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HitEnd.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API UHitEnd : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY()
	TObjectPtr<class AEKPlayer> EKPlayer;
};