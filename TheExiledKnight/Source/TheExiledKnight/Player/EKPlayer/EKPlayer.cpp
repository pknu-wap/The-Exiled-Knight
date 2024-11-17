// Made by Somalia Pirate

#include "EKPlayer.h"
#include "EKPlayerStatusComponent.h"
#include "EKPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "../Weapon/EKPlayerWeapon.h"
#include "Animation/AnimInstance.h"
#include "../EKPlayerGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../Enemy/EK_EnemyBase.h"

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

	LeftLegCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LeftLeg"));
	LeftLegCapsuleComponent->SetupAttachment(RootComponent);
	LeftLegCapsuleComponent->SetRelativeLocation(FVector(20, -30, -70));

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
}

void AEKPlayer::BeginPlay()
{
	Super::BeginPlay();

	EKPlayerController = Cast<AEKPlayerController>(this->GetController());

#pragma region Weapon Test

	// Test Change Weapon

	// Test GreatSword Version

	if (GreatSwordClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AGreatSword>(GreatSwordClass, SpawnParams);
		AttachWeaponToSpineSocket(CurrentWeapon);
		EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_Equip_GreatSword);
	}

	// Test Spear Version

	/*if (SpearClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<ASpear>(SpearClass, SpawnParams);
		AttachWeaponToSpineSocket(CurrentWeapon);
		GetCharacterMovement()->JumpZVelocity = 1000.f;
		EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_Equip_Spear);
	}*/

	// Test Staff Version Don't Select This

	/*if (StaffClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AStaff>(StaffClass, SpawnParams);
		AttachWeaponToSpineSocket(CurrentWeapon);
		EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_Equip_Staff);
	}*/

#pragma endregion

		
}

void AEKPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Test
	// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Cyan, FString::Printf(TEXT("HP : %d / %d"), PlayerStatusComponent->GetHp(), PlayerStatusComponent->GetMaxHp()));
	// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Cyan, FString::Printf(TEXT("MP : %d / %d"), PlayerStatusComponent->GetMp(), PlayerStatusComponent->GetMaxMp()));
	// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Cyan, FString::Printf(TEXT("Stamina : %d / %d"), PlayerStatusComponent->GetStamina(), PlayerStatusComponent->GetMaxStamina()));
}

#pragma region Damage

float AEKPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Hit))
	{
		return 0.f;
	}

	HitTimer();

	if (!EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_BattleState))
	{
		CurrentWeapon->PlayWeaponEquipAnimMontage(this, EKPlayerController);
	}

	EKPlayerController->BattleStateTimer();

	if (EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Defense) && PlayerStatusComponent->GetStamina() >= DefenseStamina)
	{
		if (!EKPlayerController)
		{
			return 0.f;
		}

		EKPlayerController->ConsumtionStaminaAndTimer(DefenseStamina);

		if (EKPlayerController->bIsPerfectDefense) // Perfect Defense
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Magenta, TEXT("Perfect Defense"));
		}
		else // Normal Defense
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Normal Defense"));
			PlayerStatusComponent->SetHp(-Damage * 0.3);
		}
	}
	else
	{
		PlayerStatusComponent->SetHp(-Damage);
		HitDirection(Cast<AEK_EnemyBase>(DamageCauser));
	}

	return 0.f;
}

void AEKPlayer::HitDirection(TObjectPtr<AEK_EnemyBase> Enemy)
{
	if (!Enemy)
	{
		return;
	}

	FVector PlayerLocation = this->GetActorLocation();
	FVector EnemyLocation = Enemy->GetActorLocation();

	FVector Direction = (PlayerLocation - EnemyLocation).GetSafeNormal();

	FVector PlayerForward = this->GetActorForwardVector();

	float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(Direction, PlayerForward)));

	FVector CrossProduct = FVector::CrossProduct(PlayerForward, Direction);

	if (CrossProduct.Z < 0) {
		Angle = -Angle;
	}

	HitAngle = Angle;
}

#pragma endregion

#pragma region Attach to Socket

void AEKPlayer::EquipWeapon(const FWeaponStruct& InWeaponInfo)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}

	if (InWeaponInfo.WeaponClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AEKPlayerWeapon>(InWeaponInfo.WeaponClass, SpawnParams);
		AttachWeaponToSpineSocket(CurrentWeapon);
		GetMesh()->SetAnimInstanceClass(InWeaponInfo.AnimInstance);
	}
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

#pragma endregion

#pragma region Timer

void AEKPlayer::RemoveHitTag()
{
	EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Hit);
}

void AEKPlayer::HitTimer()
{
	EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Hit);
	GetWorldTimerManager().SetTimer(HitTagHandle, this, &ThisClass::RemoveHitTag, NextHitTime, false);
}

#pragma endregion