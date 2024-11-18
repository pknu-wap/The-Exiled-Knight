// Fill out your copyright notice in the Description page of Project Settings.

//
#include "Structs/ItemStruct.h"

FItemStruct::FItemStruct()
{
    ID = 1;
    Name = "Empty";
    Description = "";
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
