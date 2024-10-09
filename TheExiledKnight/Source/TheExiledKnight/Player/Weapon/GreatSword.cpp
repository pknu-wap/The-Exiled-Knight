// Made by Somalia Pirate


#include "GreatSword.h"

// Sets default values
AGreatSword::AGreatSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
void AGreatSword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGreatSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}