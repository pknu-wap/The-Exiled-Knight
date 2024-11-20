// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EKSanctuary.generated.h"

UCLASS()
class THEEXILEDKNIGHT_API AEKSanctuary : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEKSanctuary();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void ActivateSantuary();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* SMComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UNiagaraComponent* Niagara_Santuary;

private:
	FVector CurrentScale = FVector(0, 0, 0);
	FTimerHandle ActivateHandle;
	FTimerHandle StopHandle;
};
