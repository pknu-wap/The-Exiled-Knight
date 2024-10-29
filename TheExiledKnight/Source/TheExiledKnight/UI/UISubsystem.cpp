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
	UUserWidget** layer = LayerMap.Find(LayerTag);
	if (layer) return;

	if(Widget)
		LayerMap.Add(LayerTag, Widget);
}

void UUISubsystem::UnRegisterLayer(FGameplayTag LayerTag)
{
	UUserWidget** layer = LayerMap.Find(LayerTag);
	if (!layer) return;

	(*layer)->RemoveFromParent();
	LayerMap.Remove(LayerTag);
}

void UUISubsystem::RegisterWidget(FGameplayTag WidgetTag, UUserWidget* Widget)
{
	UUserWidget** widget = WidgetMap.Find(WidgetTag);
	if (widget) return;

	WidgetMap.Add(WidgetTag, Widget);
}

void UUISubsystem::UnRegisterWidget(FGameplayTag WidgetTag)
{
	UUserWidget** widget = WidgetMap.Find(WidgetTag);
	if (widget)
	{
		(*widget)->RemoveFromParent();
		WidgetMap.Remove(WidgetTag);
	}
}

void UUISubsystem::SetLayerVisibility(FGameplayTag LayerTag, ESlateVisibility Visibility)
{
	UUserWidget** layer = LayerMap.Find(LayerTag);
	if (layer)
	{
		(*layer)->SetVisibility(Visibility);
	}
}

ESlateVisibility UUISubsystem::GetLayerVisibility(FGameplayTag LayerTag)
{
	UUserWidget** layer = LayerMap.Find(LayerTag);
	if (layer)
	{
		return (*layer)->GetVisibility();
	}

	return ESlateVisibility::SelfHitTestInvisible;
}

void UUISubsystem::SetWidgetVisibility(FGameplayTag WidgetTag, ESlateVisibility Visibility)
{
	UUserWidget** widget = WidgetMap.Find(WidgetTag);
	if (widget)
	{
		(*widget)->SetVisibility(Visibility);
	}
}

UUserWidget* UUISubsystem::GetLayer(FGameplayTag LayerTag)
{
	UUserWidget** layer = LayerMap.Find(LayerTag);
	if (layer)
	{
		return (*layer);
	}

	return nullptr;
}

UUserWidget* UUISubsystem::GetWidget(FGameplayTag WidgetTag)
{
	UUserWidget** widget = WidgetMap.Find(WidgetTag);
	if (widget)
	{
		return (*widget);
	}

	return nullptr;
}
