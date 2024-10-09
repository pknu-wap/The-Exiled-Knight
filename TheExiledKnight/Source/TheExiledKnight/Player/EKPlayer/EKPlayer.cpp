// Made by Somalia Pirate

#include "EKPlayer.h"
#include "EKPlayerStatusComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "../Weapon/GreatSword.h"

AEKPlayer::AEKPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	AEKPlayer::GetCapsuleComponent()->InitCapsuleSize(34.f, 95.f);

	PlayerStatusComponent = CreateDefaultSubobject<UEKPlayerStatusComponent>(TEXT("PlayerStatusComponent"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshFinder(TEXT("/AssetShare/Character/DARK_C_KNIGHT/MESHES/UE5/SK_DC_Knight_UE5_full_Silver"));
	AEKPlayer::GetMesh()->SetSkeletalMesh(SkeletalMeshFinder.Object);
	AEKPlayer::GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = true;

	GetCharacterMovement()->GravityScale = 3.f;
	GetCharacterMovement()->JumpZVelocity = 800.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	ConstructorHelpers::FClassFinder<AGreatSword> GreatSwordClassFinder(TEXT("/Game/EKPlayer/Blueprint/Weapon/BP_GreatSword.BP_GreatSword_C"));
	if (GreatSwordClassFinder.Succeeded())
	{
		GreatSwordClass = GreatSwordClassFinder.Class;
	}
}

void AEKPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (GreatSwordClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AGreatSword>(GreatSwordClass, SpawnParams);
		AttachGreatSwordToSocket(CurrentWeapon);
	}
}

void AEKPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EEKPlayerBehaviorState AEKPlayer::GetPlayerCurrentState()
{
	return PlayerCurrentState;
}

void AEKPlayer::SetPlayerCurrentState(EEKPlayerBehaviorState Change)
{
	PlayerCurrentState = Change;
}

void AEKPlayer::AttachGreatSwordToSocket(TObjectPtr<AGreatSword> Weapon)
{
	if (Weapon)
	{
		USkeletalMeshComponent* MeshComp = GetMesh();
		if (MeshComp)
		{
			Weapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("weapon_r_socket"));
		}
	}
}