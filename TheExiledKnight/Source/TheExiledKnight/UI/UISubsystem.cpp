// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UISubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUISubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UUISubsystem::RegisterLayer(FGameplayTag LayerTag, UUserWidget* Widget)
{
	UUserWidget* layer = *(LayerMap.Find(LayerTag));
	if (layer) return;

	if(Widget)
		LayerMap.Add(LayerTag, Widget);
}

void UUISubsystem::UnRegisterLayer(FGameplayTag LayerTag)
{
	UUserWidget* layer = *(LayerMap.Find(LayerTag));
	if (!layer) return;

	layer->RemoveFromParent();
	LayerMap.Remove(LayerTag);
}

void UUISubsystem::RemoveWidget(FGameplayTag WidgetTag)
{
	UUserWidget* widget = *(WidgetMap.Find(WidgetTag));
	if (widget)
	{
		widget->RemoveFromParent();
		WidgetMap.Remove(WidgetTag);
	}
}

void UUISubsystem::SetWidgetVisibility(FGameplayTag WidgetTag, ESlateVisibility Visibility)
{
	UUserWidget* widget = *(WidgetMap.Find(WidgetTag));
	if (widget)
	{
		widget->SetVisibility(Visibility);
	}
}
