// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "UseItem.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API UUseItem : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	class AEKPlayer* EKPlayer;

	class AEKPlayerController* EKPlayerController;
};