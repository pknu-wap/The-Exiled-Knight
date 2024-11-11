// Made by Somalia Pirate

#include "SpearTypeA.h"

ASpearTypeA::ASpearTypeA()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponAdditionalDamage = 10;
}

void ASpearTypeA::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpearTypeA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}