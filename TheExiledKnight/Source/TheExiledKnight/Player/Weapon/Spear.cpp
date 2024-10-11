// Made by Somalia Pirate


#include "Spear.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"

ASpear::ASpear()
{
	PrimaryActorTick.bCanEverTick = true;

	Spear = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Spear"));
	RootComponent = Spear;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SpearMeshFinder(TEXT("/AssetShare/Animations/Frank_Spear/Mesh/Frank_UE_Spear_Weapon_Skin"));
	if (SpearMeshFinder.Succeeded())
	{
		SpearMesh = SpearMeshFinder.Object;
	}
	Spear->SetSkeletalMesh(SpearMesh);
}

void ASpear::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

