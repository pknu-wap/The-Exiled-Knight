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
#include "Player/Weapon/Staff/Staff.h"
#include "Player/Weapon/Spear/Spear.h"
#include "Player/Weapon/GreatSword/GreatSword.h"
#include "Animation/AnimInstance.h"
#include "../EKPlayerGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../Enemy/EK_EnemyBase.h"
#include "Components/BoxComponent.h"
#include "Player/Weapon/DamageType/EKPlayerDamageType.h"
#include "Engine/DamageEvents.h"
#include "Enemy/DamageSystem/EKDamageType.h"


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

	TargetFindLockOnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TargetFindLockOnBox"));
	TargetFindLockOnBox->SetupAttachment(RootComponent);
	TargetFindLockOnBox->SetRelativeLocation(FVector(0, 0, 0));
	TargetFindLockOnBox->SetRelativeScale3D(FVector(24.f, 24.f, 20.f));
}

void AEKPlayer::BeginPlay()
{
	Super::BeginPlay();

	EKPlayerController = Cast<AEKPlayerController>(this->GetController());

	TargetFindLockOnBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTargetEnterRange);
	TargetFindLockOnBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnTargetExitRange);

#pragma region Weapon Test

	// Test Change Weapon

	// Test GreatSword Version

	/*if (GreatSwordTypeAClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AEKPlayerWeapon>(GreatSwordTypeAClass, SpawnParams);
		AttachWeaponToSpineSocket(CurrentWeapon);
		EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_Equip_GreatSword);
	}*/

	/*if (GreatSwordTypeBClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AEKPlayerWeapon>(GreatSwordTypeBClass, SpawnParams);
		AttachWeaponToSpineSocket(CurrentWeapon);
		EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_Equip_GreatSword);
	}*/

	// Test Spear Version

	/*if (SpearTypeAClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AEKPlayerWeapon>(SpearTypeAClass, SpawnParams);
		AttachWeaponToSpineSocket(CurrentWeapon);
		EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_Equip_Spear);
	}*/

	/*if (SpearTypeBClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AEKPlayerWeapon>(SpearTypeBClass, SpawnParams);
		AttachWeaponToSpineSocket(CurrentWeapon);
		EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_Equip_Spear);
	}*/

	// Test Staff Version Don't Select This

	/*if (StaffTypeAClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AEKPlayerWeapon>(StaffTypeAClass, SpawnParams);
		AttachWeaponToSpineSocket(CurrentWeapon);
		EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_Equip_Staff);
	}*/

	/*if (StaffTypeBClass)
	{
		FActorSpawnParameters SpawnParams;
		CurrentWeapon = GetWorld()->SpawnActor<AEKPlayerWeapon>(StaffTypeBClass, SpawnParams);
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

	if (LockOnTarget)
	{
		FVector Direction = LockOnTarget->GetActorLocation() - GetActorLocation();
		Direction = Direction.GetSafeNormal();

		FRotator TargetRotation = Direction.Rotation();

		TargetRotation.Pitch = EKPlayerController->GetControlRotation().Pitch;

		LockOnTargetRotation = TargetRotation;
		EKPlayerController->SetControlRotation(LockOnTargetRotation);
	}
}

#pragma region Damage

float AEKPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (!EKPlayerController || 
		EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Hit) ||
		EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_StrongHit))
	{
		return 0.f;
	}

	UEKDamageType* DamageType = Cast<UEKDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject());

	if (DamageType->IsA(UEKNormalDamageType::StaticClass()))
	{
		HitTimer();
	}
	else if (DamageType->IsA(UEKStrongDamageType::StaticClass()))
	{
		StrongHitTimer();
	}

	// if player don't equip weapon, equip weapon automatically
	if (!EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_BattleState))
	{
		if (!EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_GreatSword) &&
			!EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Spear) &&
			!EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Staff))
		{
			goto NextFunc;
		}

		CurrentWeapon->PlayWeaponEquipAnimMontage(this, EKPlayerController);
	}

NextFunc:

	EKPlayerController->BattleStateTimer();

	// About Defense Logic
	if (EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Defense) && PlayerStatusComponent->GetStamina() >= DefenseStamina)
	{
		EKPlayerController->ConsumtionStaminaAndTimer(DefenseStamina);

		if (EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Invincibility)) // Perfect Defense
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Magenta, TEXT("Perfect Defense"));
		}
		else // Normal Defense
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("Normal Defense"));
			PlayerStatusComponent->SetHp(-Damage * 0.3);
		}
	}
	else // About Normal Logic
	{
		if (EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Invincibility))
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Magenta, TEXT("Invincibility"));
		}
		else
		{
			PlayerStatusComponent->SetHp(-Damage);
			HitDirection(DamageCauser);
		}
	}

	CheckPlayerDie();

	EKPlayerController->InvincibilityTimer(0.5f);

	return 0.f;
}

bool AEKPlayer::CheckPlayerDie()
{
	if (PlayerStatusComponent->GetHp() <= 0)
	{
		EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Die);
		OnPlayerDieDelegate.Broadcast();
		return true;
	}
	return false;
}

void AEKPlayer::HitDirection(AActor* Enemy)
{
	FVector PlayerLocation = this->GetActorLocation();
	FVector EnemyLocation = Enemy->GetActorLocation();

	FVector Direction = (EnemyLocation - PlayerLocation).GetSafeNormal();
	FVector PlayerForward = this->GetActorForwardVector();

	float DotProduct = FVector::DotProduct(Direction, PlayerForward);
	float Angle = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

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

		if (InWeaponInfo.WeaponClass.Get()->IsChildOf(AGreatSword::StaticClass()))
			EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_Equip_GreatSword);
		else if (InWeaponInfo.WeaponClass.Get()->IsChildOf(ASpear::StaticClass()))
			EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_Equip_Spear);
			
		// GetMesh()->SetAnimInstanceClass(InWeaponInfo.AnimInstance);
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

void AEKPlayer::RemoveStrongHitTag()
{
	EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_StrongHit);
}

void AEKPlayer::StrongHitTimer()
{
	EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_StrongHit);
	GetWorldTimerManager().SetTimer(StrongHitTagHandle, this, &ThisClass::RemoveStrongHitTag, NextStrongHitTime, false);
}

#pragma endregion

#pragma region Lock On

void AEKPlayer::SetLockOnTarget(AActor* Target)
{
	LockOnTarget = Target;
}

void AEKPlayer::OnTargetEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AEK_EnemyBase::StaticClass()))
	{
		LockOnTargets.Add(OtherActor);
	}
}

void AEKPlayer::OnTargetExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && LockOnTargets.Contains(OtherActor))
	{
		LockOnTargets.Remove(OtherActor);
	}
}

AActor* AEKPlayer::FindNearTarget()
{
	if (LockOnTargets.Num() == 0)
	{
		return nullptr;
	}

	float NearDistance = 10000.f;
	AActor* NearTarget = nullptr;

	for (AActor* Target : LockOnTargets)
	{
		if (IsValid(Target))
		{
			float Distance = FVector::Dist(this->GetActorLocation(), Target->GetActorLocation());

			if (Distance < NearDistance)
			{
				NearDistance = Distance;
				NearTarget = Target;
			}
		}
	}

	return NearTarget;
}

#pragma endregion