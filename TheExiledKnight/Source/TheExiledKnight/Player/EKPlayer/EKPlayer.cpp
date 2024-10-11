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
#include "../Weapon/Spear.h"
#include "Animation/AnimInstance.h"

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
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = true;

	GetCharacterMovement()->GravityScale = 3.f;
	GetCharacterMovement()->JumpZVelocity = 800.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	ConstructorHelpers::FClassFinder<UAnimInstance> ABPGreatSwordFinder(TEXT("/Game/EKPlayer/Blueprint/AnimationBlueprint/ABP_GreatSword.ABP_GreatSword_C"));
	if (ABPGreatSwordFinder.Succeeded())
	{
		ABPGreatSword = ABPGreatSwordFinder.Class;
	}

	ConstructorHelpers::FClassFinder<UAnimInstance> ABPSpearFinder(TEXT("/Game/EKPlayer/Blueprint/AnimationBlueprint/ABP_Spear.ABP_Spear_C"));
	if (ABPSpearFinder.Succeeded())
	{
		ABPSpear = ABPSpearFinder.Class;
	}

	GetMesh()->AnimClass = ABPGreatSword;

	ConstructorHelpers::FClassFinder<AGreatSword> GreatSwordClassFinder(TEXT("/Game/EKPlayer/Blueprint/Weapon/BP_GreatSword.BP_GreatSword_C"));
	if (GreatSwordClassFinder.Succeeded())
	{
		GreatSwordClass = GreatSwordClassFinder.Class;
	}

	ConstructorHelpers::FClassFinder<ASpear> SpearClassFinder(TEXT("/Game/EKPlayer/Blueprint/Weapon/BP_Spear.BP_Spear_C"));
	if (SpearClassFinder.Succeeded())
	{
		SpearClass = SpearClassFinder.Class;
	}
}

void AEKPlayer::BeginPlay()
{
	Super::BeginPlay();
	// test GreatSword
	/*if (GreatSwordClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AGreatSword>(GreatSwordClass, SpawnParams);
		AttachGreatSwordToEquipSocket(CurrentWeapon);
	}*/
	
	// test Spear
	if (SpearClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<ASpear>(SpearClass, SpawnParams);
		AttachGreatSwordToEquipSocket(CurrentWeapon);
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

EEKPlayerEquipWeapon AEKPlayer::GetPlayerCurrentWeapon()
{
	return PlayerCurrentWeapon;
}

void AEKPlayer::SetPlayerCurrentWeapon(EEKPlayerEquipWeapon Change)
{
	PlayerCurrentWeapon = Change;
}

TObjectPtr<AEKPlayerWeapon> AEKPlayer::GetCurrentWeapon()
{
	return CurrentWeapon;
}

void AEKPlayer::AttachGreatSwordToEquipSocket(TObjectPtr<AEKPlayerWeapon> Weapon)
{
	if (Weapon)
	{
		USkeletalMeshComponent* MeshComp = GetMesh();
		if (MeshComp)
		{
			Weapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("weapon_equip_socket"));
		}
	}
}

void AEKPlayer::AttachGreatSwordToHandSocket(TObjectPtr<AEKPlayerWeapon> Weapon)
{
	if (Weapon)
	{
		USkeletalMeshComponent* MeshComp = GetMesh();
		if (MeshComp)
		{
			Weapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("weapon_right_hand_socket"));
		}
	}
}