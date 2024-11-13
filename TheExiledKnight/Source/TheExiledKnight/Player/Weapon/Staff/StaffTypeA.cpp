// Made by Somalia Pirate

#include "StaffTypeA.h"

AStaffTypeA::AStaffTypeA()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;

	Staff->SetStaticMesh(StaffMesh);

	WeaponAdditionalDamage = 5;
}

void AStaffTypeA::BeginPlay()
{
	Super::BeginPlay();

}

void AStaffTypeA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}