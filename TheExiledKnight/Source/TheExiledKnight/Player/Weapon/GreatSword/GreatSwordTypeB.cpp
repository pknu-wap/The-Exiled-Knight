// Made by Somalia Pirate

#include "GreatSwordTypeB.h"

AGreatSwordTypeB::AGreatSwordTypeB()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;

	// Edit Weapon Default Damage Here
	WeaponAdditionalDamage = 20;
}

void AGreatSwordTypeB::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGreatSwordTypeB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}