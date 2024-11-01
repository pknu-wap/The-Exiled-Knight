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
#include "../Weapon/Staff.h"
#include "Animation/AnimInstance.h"
#include "../EKPlayerGameplayTags.h"

AEKPlayer::AEKPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	AEKPlayer::GetCapsuleComponent()->InitCapsuleSize(34.f, 95.f);

	PlayerStatusComponent = CreateDefaultSubobject<UEKPlayerStatusComponent>(TEXT("PlayerStatusComponent"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshFinder(TEXT("/AssetShare/Character/DARK_C_KNIGHT/MESHES/UE5/SK_DC_Knight_UE5_full_Silver"));
	AEKPlayer::GetMesh()->SetSkeletalMesh(SkeletalMeshFinder.Object);
	AEKPlayer::GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -100), FRotator(0, -90, 0));

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
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
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

	ConstructorHelpers::FClassFinder<UAnimInstance> ABPStaffFinder(TEXT("/Game/EKPlayer/Blueprint/AnimationBlueprint/ABP_Staff.ABP_Staff_C"));
	if (ABPStaffFinder.Succeeded())
	{
		ABPStaff = ABPStaffFinder.Class;
	}

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

	ConstructorHelpers::FClassFinder<AStaff> StaffClassFinder(TEXT("/Game/EKPlayer/Blueprint/Weapon/BP_Staff.BP_Staff_C"));
	if (StaffClassFinder.Succeeded())
	{
		StaffClass = StaffClassFinder.Class;
	}
}

void AEKPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Test Change Weapon

	// Test GreatSword Version

	if (GreatSwordClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AGreatSword>(GreatSwordClass, SpawnParams);
		AttachWeaponToSpineSocket(CurrentWeapon);
		GetMesh()->SetAnimInstanceClass(ABPGreatSword);
	}
	
	// Test Spear Version

	/*if (SpearClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<ASpear>(SpearClass, SpawnParams);
		AttachWeaponToSpineSocket(CurrentWeapon);
		GetCharacterMovement()->JumpZVelocity = 1000.f;
		GetMesh()->SetAnimInstanceClass(ABPSpear);
	}*/

	// Test Staff Version Don't Select This

	/*if (StaffClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AStaff>(StaffClass, SpawnParams);
		AttachWeaponToSpineSocket(CurrentWeapon);
		GetMesh()->SetAnimInstanceClass(ABPStaff);
	}*/
}

void AEKPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Test
	// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Cyan, FString::Printf(TEXT("HP : %d / %d"), PlayerStatusComponent->GetHp(), PlayerStatusComponent->GetMaxHp()));
	// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Cyan, FString::Printf(TEXT("MP : %d / %d"), PlayerStatusComponent->GetMp(), PlayerStatusComponent->GetMaxMp()));
	// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Cyan, FString::Printf(TEXT("Stamina : %d / %d"), PlayerStatusComponent->GetStamina(), PlayerStatusComponent->GetMaxStamina()));
}

TObjectPtr<AEKPlayerWeapon> AEKPlayer::GetCurrentWeapon()
{
	return CurrentWeapon;
}

TObjectPtr<UEKPlayerStatusComponent> AEKPlayer::GetPlayerStatusComponent()
{
	return PlayerStatusComponent;
}

void AEKPlayer::AttackHit()
{
	CurrentWeapon->AttackHit(this, CurrentWeapon->GetWeaponCapsuleComponent());
}

float AEKPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GetPlayerStatusComponent()->TakeDamage(Damage);
	return 0.f;
}

void AEKPlayer::AttachWeaponToSpineSocket(TObjectPtr<AEKPlayerWeapon> Weapon)
{
	if (Weapon)
	{
		Weapon->AttachWeaponToSpineSocket(Weapon, this);
	}
}

void AEKPlayer::AttachWeaponToHandSocket(TObjectPtr<AEKPlayerWeapon> Weapon)
{
	if (Weapon)
	{
		Weapon->AttachWeaponToHandSocket(Weapon, this);
	}
}