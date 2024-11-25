// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Anvil/Anvil.h"
#include "UI/UISubsystem.h"
#include "EKGameplayTags.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAnvil::AAnvil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnvil::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnvil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnvil::Interact()
{
	UUISubsystem* UISystem = GetGameInstance()->GetSubsystem<UUISubsystem>();
	if (!UISystem) return;
	UISystem->SetLayerVisibility(FEKGameplayTags::Get().UI_Layer_GameMenu, ESlateVisibility::SelfHitTestInvisible);
	UISystem->SetWidgetVisibility(FEKGameplayTags::Get().UI_Widget_GameMenu_UpgradeEquipment, ESlateVisibility::SelfHitTestInvisible);

	APlayerController* pc = UGameplayStatics::GetPlayerController(this, 0);
	if (pc)
	{
		FInputModeUIOnly UIInputMode;
		pc->SetInputMode(UIInputMode);
		pc->SetShowMouseCursor(true);
	}
}


