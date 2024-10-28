// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_GameMenu_Button.generated.h"

UENUM(BlueprintType)
enum class EGameMenuCategory : uint8
{
	Inventory		UMETA(DisplayName = "Inventory"),
	Equipment		UMETA(DisplayName = "Equipment"),
	Option			UMETA(DisplayName = "Option"),
	Quit			UMETA(DisplayName = "Quit"),
};

class UButton;

UCLASS()
class THEEXILEDKNIGHT_API UWidget_GameMenu_Button : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGameMenuCategory MenuCategory;

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, EditAnywhere)
	UButton* Button_Menu;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void MenuButtonClicked();

};
