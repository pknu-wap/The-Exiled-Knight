// Made by Somalia Pirate


#include "Staff.h"

AStaff::AStaff()
{
	PrimaryActorTick.bCanEverTick = true;

	Staff = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Staff"));
	RootComponent = Staff;

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaffMeshFinder(TEXT("/AssetShare/Animations/EssentialAnimation/MagicStaff/Demo/Mannequin/Weapon/SM_Staff"));
	if (StaffMeshFinder.Succeeded())
	{
		StaffMesh = StaffMeshFinder.Object;
	}
	Staff->SetStaticMesh(StaffMesh);
}

void AStaff::BeginPlay()
{
	Super::BeginPlay();

}

void AStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
