// Made by Somalia Pirate


#include "GreatSword.h"

AGreatSword::AGreatSword()
{
	PrimaryActorTick.bCanEverTick = true;

	GreatSword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GreatSword"));
	RootComponent = GreatSword;

	ConstructorHelpers::FObjectFinder<UStaticMesh> GreatSwordMeshFinder(TEXT("/AssetShare/Animations/GreatSword/GreatSword/Weapon/GreatSword_01"));
	if (GreatSwordMeshFinder.Succeeded())
	{
		GreatSwordMesh = GreatSwordMeshFinder.Object;
	}
	GreatSword->SetStaticMesh(GreatSwordMesh);
}

void AGreatSword::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGreatSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}