// Made by Somalia Pirate

#include "SpearTypeB.h"

ASpearTypeB::ASpearTypeB()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponAdditionalDamage = 10;
}

void ASpearTypeB::BeginPlay()
{
	Super::BeginPlay();

}

void ASpearTypeB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}