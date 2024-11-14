// Made by Somalia Pirate

#include "StaffTypeB.h"

AStaffTypeB::AStaffTypeB()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;

	Staff->SetStaticMesh(StaffMesh);

	WeaponAdditionalDamage = 5;

	DamageValue = 0.3;
}

void AStaffTypeB::BeginPlay()
{
	Super::BeginPlay();

}

void AStaffTypeB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}