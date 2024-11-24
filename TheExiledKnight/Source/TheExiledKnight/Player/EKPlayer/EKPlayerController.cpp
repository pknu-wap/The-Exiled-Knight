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
#include "Components/SlotComponent.h"
#include "UI/UISubsystem.h"
#include "Blueprint/UserWidget.h"
#include "EKGameplayTags.h"
#include "../Weapon/DamageType/EKPlayerDamageType.h"
#include "Item/EKItem_Base.h"
#include "Subsystems/InventorySubsystem.h"
#include "DrawDebugHelpers.h"
#include "Interfaces/UInteractableInterface.h"
#include "Player/DomainExpansion/DomainExpansionBase.h"

AEKPlayerController::AEKPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	SlotComponent = CreateDefaultSubobject<USlotComponent>(TEXT("SlotComponent"));
}

void AEKPlayerController::BeginPlay()
{
	Super::BeginPlay();

	EKPlayer = Cast<AEKPlayer>(GetPawn());

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMCDefault, 0);
	}

	InventoryComponent = NewObject<UInventoryComponent>(this, TEXT("Inventory"));

	InventoryComponent->AddItemDelegate.AddDynamic(this, &AEKPlayerController::DestroyItem);

	TryInteractLoop();
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

		EnhancedInputComponent->BindAction(IALockOn, ETriggerEvent::Started, this, &ThisClass::LockOnStarted);

		EnhancedInputComponent->BindAction(IADomainExpansion, ETriggerEvent::Started, this, &ThisClass::DomainExpansionStarted);

		EnhancedInputComponent->BindAction(IAGameMenu, ETriggerEvent::Started, this, &ThisClass::OnPressed_GameMenu);
		EnhancedInputComponent->BindAction(IA_Up, ETriggerEvent::Started, this, &ThisClass::OnPressed_Up);
		EnhancedInputComponent->BindAction(IA_Down, ETriggerEvent::Started, this, &ThisClass::OnPressed_Down);
		EnhancedInputComponent->BindAction(IA_Left, ETriggerEvent::Started, this, &ThisClass::OnPressed_Left);
		EnhancedInputComponent->BindAction(IA_Right, ETriggerEvent::Started, this, &ThisClass::OnPressed_Right);

	}
}

void AEKPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//FindInteractableObjects();
}

#pragma region Move

void AEKPlayerController::MoveTriggered(const FInputActionValue& InputValue)
{
	if (EKPlayer->CheckPlayerDie())
	{
		return;
	}

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
	LookAxisVector = InputValue.Get<FVector2D>();

	EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Look);

	if (!EKPlayer)
	{
		return;
	}

	EKPlayer->AddControllerYawInput(LookAxisVector.X);
	EKPlayer->AddControllerPitchInput(LookAxisVector.Y);
}

void AEKPlayerController::LookRelease(const FInputActionValue& InputValue)
{
	EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Look);
}

void AEKPlayerController::LockOnStarted(const FInputActionValue& InputValue)
{
	if (EKPlayer->GetLockOnTarget())
	{
		EKPlayer->SetLockOnTarget(nullptr);
	}
	else
	{
		EKPlayer->SetLockOnTarget(EKPlayer->FindNearTarget());
	}
}

#pragma endregion

#pragma region Jump

void AEKPlayerController::JumpStarted(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (EKPlayer->CheckPlayerDie())
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

	if (EKPlayer->CheckPlayerDie())
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

	if (EKPlayer->CheckPlayerDie())
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

			InvincibilityTimer(0.65f);

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

	if (EKPlayer->CheckPlayerDie())
	{
		return;
	}

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Jump) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Attack) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Dodge))
	{
		return;
	}

	// if Player sets lock on, Camera view changes
	if (EKPlayer->GetLockOnTarget())
	{
		EKPlayer->SetActorRotation(EKPlayer->GetLockOnTargetRotation());
	}

	BattleStateTimer();

	if (!bIsEquipWeapon)
	{
		if (!EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_GreatSword) &&
			!EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Spear) &&
			!EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Staff))
		{
			return;
		}

		EKPlayer->GetCurrentWeapon()->PlayWeaponEquipAnimMontage(EKPlayer, this);
	}
	else
	{
		EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_SitDown);

		EKPlayer->GetCurrentWeapon()->PlayAttackStartAnimMontage(EKPlayer, this);
	}
}

void AEKPlayerController::SkillStarted(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (EKPlayer->CheckPlayerDie())
	{
		return;
	}

	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Jump) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Attack) ||
		EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_Dodge))
	{
		return;
	}

	// if Player sets lock on, Camera view changes
	if (EKPlayer->GetLockOnTarget())
	{
		EKPlayer->SetActorRotation(EKPlayer->GetLockOnTargetRotation());
	}

	BattleStateTimer();

	if (!bIsEquipWeapon)
	{
		if (!EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_GreatSword) &&
			!EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Spear) &&
			!EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Staff))
		{
			return;
		}

		EKPlayer->GetCurrentWeapon()->PlayWeaponEquipAnimMontage(EKPlayer, this);
	}
	else
	{
		EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_SitDown);

		EKPlayer->GetCurrentWeapon()->PlaySkillStartAnimMontage(EKPlayer, this);
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

	if (EKPlayer->CheckPlayerDie())
	{
		return;
	}

	// if Player sets lock on, Camera view changes
	if (EKPlayer->GetLockOnTarget())
	{
		EKPlayer->SetActorRotation(EKPlayer->GetLockOnTargetRotation());
	}

	BattleStateTimer();

	if (!bIsEquipWeapon)
	{
		if (!EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_GreatSword) &&
			!EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Spear) &&
			!EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Staff))
		{
			return;
		}

		EKPlayer->GetCurrentWeapon()->PlayWeaponEquipAnimMontage(EKPlayer, this);
	}
	else
	{
		EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Defense);
		EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_SitDown);
		EKPlayer->GetCurrentWeapon()->AttachToDefenseSocket(EKPlayer->GetCurrentWeapon(), EKPlayer);
		InvincibilityTimer(0.2f);
	}
}

void AEKPlayerController::WeaponDefenseRelease(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (!EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_GreatSword) &&
		!EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Spear) &&
		!EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_Equip_Staff))
	{
		return;
	}

	EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Defense);
	EKPlayer->GetCurrentWeapon()->AttachWeaponToHandSocket(EKPlayer->GetCurrentWeapon(), EKPlayer);
}

#pragma endregion

#pragma region Domain Expansion

void AEKPlayerController::DomainExpansionStarted(const FInputActionValue& InputValue)
{
	if (EKPlayer->EKPlayerStateContainer.HasTag(EKPlayerGameplayTags::EKPlayer_State_DomainExpansion))
	{
		return;
	}

	if (!CurrentDomainExpansion)
	{
		return;
	}

	EKPlayer->GetWorld()->SpawnActor<ADomainExpansionBase>(CurrentDomainExpansion, EKPlayer->GetActorLocation(), EKPlayer->GetActorRotation());
}

void AEKPlayerController::ChangeDomainExpansion(int32 Row)
{
	if (EKPlayerGameInstance)
	{
		FEKPlayerDomainExpansion* EKPlayerDomainExpansionDataTemp = EKPlayerGameInstance->GetEKPlayerDomainExpansion(Row);
		EKPlayerDomainExpansionData = *EKPlayerDomainExpansionDataTemp;
		CurrentDomainExpansion = DomainExpansions[EKPlayerDomainExpansionData.DomainExpansionID];
	}
}

#pragma endregion

#pragma region etc

void AEKPlayerController::WeaponChangeStarted(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (EKPlayer->CheckPlayerDie())
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

	if (EKPlayer->CheckPlayerDie())
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

	if (InventoryComponent != nullptr)
		InventoryComponent->UseItem(*GetGameInstance()->GetSubsystem<UInventorySubsystem>()->GetItemInfo(3));

	EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_UseItem);
}

void AEKPlayerController::SitDownStarted(const FInputActionValue& InputValue)
{
	if (!EKPlayer)
	{
		return;
	}

	if (EKPlayer->CheckPlayerDie())
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

#pragma endregion

#pragma region Inventory and UI

void AEKPlayerController::Interact(const FInputActionValue& InputValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact"));

	if (Item != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can Interact with Item"));

		InventoryComponent->AddItem(Item->GetItemInfo(), Item->GetItemQuantity());
	}

	if (InteractableActor)
		InteractableActor->Interact();
}

void AEKPlayerController::FindInteractableObjects()
{
	FVector Location;
	FRotator Rotation;
	TArray<FHitResult> HitResults;

	EKPlayer->GetActorEyesViewPoint(Location, Rotation);

	FVector Start = Location;
	FVector End = Start + Rotation.Vector() * 500.0f;

	// ignore player

	FCollisionQueryParams traceParams;
	GetWorld()->LineTraceMultiByChannel(HitResults, Start, End, ECC_Visibility, traceParams);

	for (FHitResult& HitResult : HitResults)
	{
		InteractableActor = Cast<IUInteractableInterface>(HitResult.GetActor());
		Item = Cast<AEKItem_Base>(HitResult.GetActor());

		if (Item != nullptr)
			break;
	}

	FColor Color = Item ? FColor::Green : FColor::Red;

	DrawDebugLine(GetWorld(), Start, End, Color, false, 2.0f);

	if (Item)
	{
		// Show Interact UI

	}

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

void AEKPlayerController::OnPressed_Up(const FInputActionValue& InputValue)
{
	if (SlotComponent)
		SlotComponent->UpdateActiveSlot(EInputType::Up);
}

void AEKPlayerController::OnPressed_Down(const FInputActionValue& InputValue)
{
	if (SlotComponent)
		SlotComponent->UpdateActiveSlot(EInputType::Down);
}

void AEKPlayerController::OnPressed_Left(const FInputActionValue& InputValue)
{
	if (SlotComponent)
		SlotComponent->UpdateActiveSlot(EInputType::Left);
}

void AEKPlayerController::OnPressed_Right(const FInputActionValue& InputValue)
{
	if (SlotComponent)
		SlotComponent->UpdateActiveSlot(EInputType::Right);
}

void AEKPlayerController::TryInteractLoop()
{
	GetWorldTimerManager().SetTimer(InteractCheckHandle, this, &ThisClass::FindInteractableObjects, InteractCheckTime, true);
}

#pragma endregion

#pragma region Timer

void AEKPlayerController::DestroyItem()
{
	if (Item)
		Item->Destroy();
}

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

void AEKPlayerController::RemoveAttackTag()
{
	EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
}

void AEKPlayerController::RemoveAttackTagTimer(float Time)
{
	EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Attack);
	GetWorldTimerManager().SetTimer(StaffBaseSkillEndHandle, this, &ThisClass::RemoveAttackTag, Time, false);
}

void AEKPlayerController::SetInvincibility()
{
	EKPlayer->EKPlayerStateContainer.RemoveTag(EKPlayerGameplayTags::EKPlayer_State_Invincibility);
}

void AEKPlayerController::InvincibilityTimer(float Time)
{
	GetWorldTimerManager().SetTimer(InvincibilityHandle, this, &ThisClass::SetInvincibility, Time, false);
	EKPlayer->EKPlayerStateContainer.AddTag(EKPlayerGameplayTags::EKPlayer_State_Invincibility);
}

#pragma endregion