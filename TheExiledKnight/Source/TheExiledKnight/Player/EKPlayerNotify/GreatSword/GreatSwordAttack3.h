// Made by Somalia Pirate

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GreatSwordAttack3.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API UGreatSwordAttack3 : public UAnimNotifyState
{
	GENERATED_BODY()
	
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY()
	TObjectPtr<class AEKPlayer> EKPlayer;

	UPROPERTY()
	TObjectPtr<class AEKPlayerController > EKPlayerController;
};