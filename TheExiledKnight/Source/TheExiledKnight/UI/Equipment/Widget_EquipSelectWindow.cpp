// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment/Widget_EquipSelectWindow.h"
#include "UI/Equipment/Widget_EquipSelect_ContentList.h"

void UWidget_EquipSelectWindow::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_EquipSelectWindow::UpdateContents(EItemCategory Category)
{
	ContentList->UpdateContents(Category);
}
