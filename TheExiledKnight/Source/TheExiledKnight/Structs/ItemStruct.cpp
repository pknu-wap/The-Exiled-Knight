// Fill out your copyright notice in the Description page of Project Settings.

//
#include "Structs/ItemStruct.h"

FItemStruct::FItemStruct()
{
    UE_LOG(LogTemp, Warning, TEXT("FItemStruct() called"));

    ID = 1;
    Name = "Empty";
    Description = TEXT("");
    ItemCategory = EItemCategory::None;
    Icon = nullptr;
    MaxStackSize = 1;
    ItemValue = 0;
    ItemLevel = 1;
    bUseable = false;
    bDestroyable = false;
}

FWeaponStruct::FWeaponStruct()
{

}

FItemObject::FItemObject()
{

}

FLevelRate::FLevelRate()
{
}

FRune::FRune()
{
}
