// Made by Somalia Pirate

#include "GreatSwordTypeA.h"

AGreatSwordTypeA::AGreatSwordTypeA()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;

	// Edit Weapon Default Damage Here
	WeaponAdditionalDamage = 20;
}

void AGreatSwordTypeA::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGreatSwordTypeA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}