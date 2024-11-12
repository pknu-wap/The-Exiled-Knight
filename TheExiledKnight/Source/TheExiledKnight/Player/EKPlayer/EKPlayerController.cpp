// Made by Somalia Pirate

#include "EKPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EKPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Weapon/EKPlayerWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EKPlayerStatusComponent.h"
#include "../EKPlayerGameplayTags.h"
#include "Components/InventoryComponent.h"
#include "UI/UISubsystem.h"
#include "Blueprint/UserWidget.h"
#include "EKGameplayTags.h"
#include "../Weapon/DamageType/EKPlayerDamageType.h"

AEKPlayerController::AEKPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

void AEKPlayerController::BeginPlay()
{
	Super::BeginPlay();

	EKPlayer = Cast<AEKPlayer>(GetPawn());

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMCDefault, 0);
	}
}

void AEKPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &ThisClass::MoveTriggered);
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Completed, this, &ThisClass::MoveRelease);
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Canceled, this, &ThisClass::MoveRelease);

		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Triggered, this, &ThisClass::LookTriggered);
		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Completed, this, &ThisClass::LookRelease);
		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Canceled, this, &ThisClass::LookRelease);

		EnhancedInputComponent->BindAction(IAJump, ETriggerEvent::Started, this, &ThisClass::JumpStarted);
		EnhancedInputComponent->BindAction(IAJump, ETriggerEvent::Triggered, this, &ThisClass::JumpTriggered);

		EnhancedInputComponent->BindAction(IAWeaponChange, ETriggerEvent::Triggered, this, &ThisClass::WeaponChangeStarted);
		EnhancedInputComponent->BindAction(IAUsePotion, ETriggerEvent::Started, this, &ThisClass::UsePotionStarted);

		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Started, this, &ThisClass::SprintAndDodgeStarted);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Triggered, this, &ThisClass::SprintAndDodgeTriggered);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Completed, this, &ThisClass::SprintAndDodgeRelease);
		EnhancedInputComponent->BindAction(IASprintAndDodge, ETriggerEvent::Canceled, this, &ThisClass::SprintAndDodgeRelease);

		EnhancedInputComponent->BindAction(IAWeaponAttack, ETriggerEvent::Started, this, &ThisClass::WeaponAttackStarted);

		EnhancedInputComponent->BindAction(IAWeaponDefense, ETriggerEvent::Started, this, &ThisClass::WeaponDefenseStarted);
		EnhancedInputComponent->BindAction(IAWeaponDefense, ETriggerEvent::Completed, this, &ThisClass::WeaponDefenseRelease);
		EnhancedInputComponent->BindAction(IAWeaponDefense, ETriggerEvent::Canceled, this, &ThisClass::WeaponDefenseRelease);

		EnhancedInputComponent->BindAction(IASitDown, ETriggerEvent::Started, this, &ThisClass::SitDownStarted);

		EnhancedInputComponent->BindAction(IAInteract, ETriggerEvent::Started, this, &ThisClass::Interact);

		EnhancedInputComponent->BindAction(IASkill, ETriggerEvent::Started, this, &ThisClass::SkillStarted);
		
		EnhancedInputComponent->BindAction(IATest, ETriggerEvent::Started, this, &ThisClass::TestStarted);
	}
}

void AEKPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

#pragma region Move

void AEKPlayerController::MoveTriggered(const FInputActionValue& InputValue)
{
	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Attack) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Defense))
	{
		return;
	}

	EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Move);

	FVector2D MovementVector = InputValue.Get<FVector2D>();

	FRotator Rotator = GetControlRotation();

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Dodge))
	{
		return;
	}

	if (MovementVector.X != 0)
	{
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.X);
	}

	if (MovementVector.Y != 0)
	{
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.Y);
	}
}

void AEKPlayerController::MoveRelease(const FInputActionValue& InputValue)
{
	EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Move);
}

#pragma endregion

#pragma region Look

void AEKPlayerController::LookTriggered(const FInputActionValue& InputValue)
{
	FVector2D LookAxisVector = InputValue.Get<FVector2D>();

	EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Look);

	if (EKPlayer)
	{
		EKPlayer->AddControllerYawInput(LookAxisVector.X);
		EKPlayer->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AEKPlayerController::LookRelease(const FInputActionValue& InputValue)
{
	EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Look);
}

#pragma endregion

#pragma region Jump

void AEKPlayerController::JumpStarted(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < JumpStamina)
	{
		return;
	}

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Attack) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Jump) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Defense) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_SitDown) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Dodge))
	{
		return;
	}

	EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Jump);

	EKPlayer->Jump();

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_BattleState))
	{
		ConsumtionStaminaAndTimer(JumpStamina);
	}
}

void AEKPlayerController::JumpTriggered(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (!EKPlayer->GetMovementComponent()->IsFalling())
	{
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Jump);
	}
}

#pragma endregion

#pragma region Sprint and Dodge

void AEKPlayerController::SprintAndDodgeStarted(const FInputActionValue& InputValue)
{
	SpaceKeyPressStart = GetWorld()->GetTimeSeconds();
}

void AEKPlayerController::SprintAndDodgeTriggered(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Attack) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Defense) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Jump))
	{
		return;
	}

	if (EKPlayer->GetPlayerStatusComponent()->GetStamina() < SprintStamina)
	{
		EKPlayer->GetCharacterMovement()->MaxWalkSpeed = EKPlayerWalkSpeed;
		return;
	}

	KeyPressDuration = GetWorld()->GetTimeSeconds() - SpaceKeyPressStart;

	if (KeyPressDuration >= NeedDodgeThresholdTime)
	{
		if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Attack))
		{
			return;
		}

		if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_SitDown))
		{
			EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_SitDown);
		}

		EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Sprint);
		EKPlayer->GetCharacterMovement()->MaxWalkSpeed = EKPlayerSprintSpeed;

		if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_BattleState))
		{
			ConsumtionStaminaAndTimer(SprintStamina);
		}
	}
}

void AEKPlayerController::SprintAndDodgeRelease(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Sprint);

	FVector MoveInput = EKPlayer->GetLastMovementInputVector();

	if (KeyPressDuration < NeedDodgeThresholdTime && EKPlayer->GetPlayerStatusComponent()->GetStamina() >= DodgeStamina)
	{
		if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Jump) ||
			EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Attack) ||
			EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Defense) ||
			EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Dodge) ||
			EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_SitDown) ||
			EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_UseItem))
		{
			return;
		}

		if (MoveInput.IsNearlyZero())
		{
			EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Dodge);
			EKPlayer->PlayAnimMontage(BackStepAnim);

			if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_BattleState))
			{
				ConsumtionStaminaAndTimer(BackStepStamina);
			}
		}
		else
		{
			EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Dodge);
			EKPlayer->PlayAnimMontage(DodgeAnim);

			if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_BattleState))
			{
				ConsumtionStaminaAndTimer(DodgeStamina);
			}
		}
	}

	EKPlayer->GetCharacterMovement()->MaxWalkSpeed = EKPlayerWalkSpeed;
}

#pragma endregion

#pragma region Attack

void AEKPlayerController::WeaponAttackStarted(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Jump) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Attack) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Dodge))
	{
		return;
	}

	BattleStateTimer();

	if (!bIsEquipWeapon)
	{
		EKPlayer->GetCurrentWeapon()->PlayWeaponEquipAnimMontage(EKPlayer, this);
	}
	else
	{
		EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_SitDown);

		EKPlayer->GetCurrentWeapon()->PlayAttackStartAnimMontage(EKPlayer, this);

		EKPlayer->bUseControllerRotationYaw = true;
	}
}

void AEKPlayerController::SkillStarted(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Jump) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Attack) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Dodge))
	{
		return;
	}

	BattleStateTimer();

	if (!bIsEquipWeapon)
	{
		EKPlayer->GetCurrentWeapon()->PlayWeaponEquipAnimMontage(EKPlayer, this);
	}
	else
	{
		EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_SitDown);

		EKPlayer->GetCurrentWeapon()->PlaySkillStartAnimMontage(EKPlayer, this);

		EKPlayer->bUseControllerRotationYaw = true;
	}
}

#pragma endregion

#pragma region Defense

void AEKPlayerController::WeaponDefenseStarted(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	BattleStateTimer();

	if (!bIsEquipWeapon)
	{
		EKPlayer->GetCurrentWeapon()->PlayWeaponEquipAnimMontage(EKPlayer, this);
	}
	else
	{
		EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Defense);
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_SitDown);
		PerfectDefenseTimer();
	}
}

void AEKPlayerController::WeaponDefenseRelease(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}
	EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Defense);
}

#pragma endregion

#pragma region etc

void AEKPlayerController::WeaponChangeStarted(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	EKPlayer->GetCurrentWeapon()->PlayWeaponEquipAnimMontage(EKPlayer, this);
}

void AEKPlayerController::UsePotionStarted(const FInputActionValue& InputValue)
{
	if (!EKPlayer || !UsePotionAnim)
	{
		return;
	}

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Jump) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Attack) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Dodge) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_UseItem))
	{
		return;
	}

	EKPlayer->GetPlayerStatusComponent()->SetHp(10);
	EKPlayer->GetPlayerStatusComponent()->SetMp(10);
	EKPlayer->PlayAnimMontage(UsePotionAnim);
	EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_UseItem);
}

void AEKPlayerController::SitDownStarted(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Jump) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Attack) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Dodge) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_UseItem))
	{
		return;
	}

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_SitDown))
	{
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_SitDown);
		EKPlayer->GetCharacterMovement()->MaxWalkSpeed = 200.f;
	}
	else
	{
		EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_SitDown);
		EKPlayer->GetCharacterMovement()->MaxWalkSpeed = 100.f;
	}
}

void AEKPlayerController::TestStarted(const FInputActionValue& InputValue)
{
	TSubclassOf<UEKPlayerDamageType> PlayerDamageType = UEKPlayerDamageType::StaticClass();
	UGameplayStatics::ApplyDamage(EKPlayer, 10, this, EKPlayer->GetCurrentWeapon(), PlayerDamageType);
}

#pragma endregion

void AEKPlayerController::Interact(const FInputActionValue& InputValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact"));
}

void AEKPlayerController::FindInteractableObjects()
{

}

void AEKPlayerController::OnPressed_GameMenu(const FInputActionValue& InputValue)
{
	UUISubsystem* UISystem = GetGameInstance()->GetSubsystem<UUISubsystem>();
	if (!UISystem) return;

	UUserWidget* layer_GameMenu = UISystem->GetLayer(FEKGameplayTags::Get().UI_Layer_GameMenu);
	UUserWidget* widget_GameMenu = UISystem->GetWidget(FEKGameplayTags::Get().UI_Widget_GameMenu_GameMenu);

	if (layer_GameMenu && layer_GameMenu->GetVisibility() == ESlateVisibility::Collapsed)
	{
		layer_GameMenu->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		widget_GameMenu->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		widget_GameMenu->SetFocus();

		FInputModeUIOnly UIInputMode;
		SetInputMode(UIInputMode);
		SetShowMouseCursor(true);
	}
	else if (widget_GameMenu && widget_GameMenu->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
	{
		layer_GameMenu->SetVisibility(ESlateVisibility::Collapsed);
		widget_GameMenu->SetVisibility(ESlateVisibility::Collapsed);

		FInputModeGameOnly GameInputMode;
		SetInputMode(GameInputMode);
		SetShowMouseCursor(false);
	}
}

#pragma region Timer

void AEKPlayerController::SetStaminaRecoveryTime()
{
	EKPlayer->GetPlayerStatusComponent()->bCanStaminaRecovery = true;
}

void AEKPlayerController::ConsumtionStaminaAndTimer(int32 Stamina)
{
	EKPlayer->GetPlayerStatusComponent()->SetStamina(-Stamina);
	EKPlayer->GetPlayerStatusComponent()->bCanStaminaRecovery = false;
	GetWorldTimerManager().SetTimer(StaminaRecoveryHandle, this, &ThisClass::SetStaminaRecoveryTime, StaminaRecoveryTime, false);
}

void AEKPlayerController::SetAttackComboNext()
{
	EKPlayer->GetCurrentWeapon()->SetAttackComboNext();
}

void AEKPlayerController::ResetAttackCombo()
{
	EKPlayer->GetCurrentWeapon()->ResetAttackCombo();
}

void AEKPlayerController::SetAttackEndTimer(float Time)
{
	GetWorldTimerManager().SetTimer(AttackEndHandle, this, &ThisClass::ResetAttackCombo, Time, false);
}

void AEKPlayerController::SetPerfectDefense()
{
	bIsPerfectDefense = false;
}

void AEKPlayerController::PerfectDefenseTimer()
{
	bIsPerfectDefense = true;
	GetWorldTimerManager().SetTimer(PerfectDefenseHandle, this, &ThisClass::SetPerfectDefense, PerfectDefenseTime, false);
}

void AEKPlayerController::SetBattleStateEnd()
{
	EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_BattleState);
	if (bIsEquipWeapon)
	{
		EKPlayer->GetCurrentWeapon()->PlayWeaponEquipAnimMontage(EKPlayer, this);
	}
}

void AEKPlayerController::BattleStateTimer()
{
	EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_BattleState);
	GetWorldTimerManager().SetTimer(BattleStateHandle, this, &ThisClass::SetBattleStateEnd, BattleEndTime, false);
}

#pragma endregion