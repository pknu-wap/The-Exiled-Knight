// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EKEnums.h"
#include "ItemStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
    GENERATED_BODY()

    FItemStruct();
    FItemStruct(const FItemStruct& Other)
    {
        ID = Other.ID;
        Name = Other.Name;
        Description = Other.Description;
        ItemCategory = Other.ItemCategory;
        Icon = Other.Icon;
        MaxStackSize = Other.MaxStackSize;
        ItemValue = Other.ItemValue;
        ItemLevel = Other.ItemLevel;
        bUseable = Other.bUseable;
        bDestroyable = Other.bDestroyable;
    };

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 ID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemCategory ItemCategory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 MaxStackSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int ItemValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int ItemLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseable = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bDestroyable = true;
};

USTRUCT(BlueprintType)
struct FWeaponStruct : public FTableRowBase
{
    GENERATED_BODY()

    FWeaponStruct();
    FWeaponStruct(const FWeaponStruct& Other)
    {
        ID = Other.ID;
        Name = Other.Name;
        SocketName = Other.SocketName;
        AnimInstance = Other.AnimInstance;
        SkillAnim = Other.SkillAnim;
        STRRate = Other.STRRate;
        DEXRate = Other.DEXRate;
        INTRate = Other.INTRate;
        StaticMesh = Other.StaticMesh;
        SkeletonMesh = Other.SkeletonMesh;
    };

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 ID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Name = "Weapon";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SocketName = "Socket";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimInstance* AnimInstance = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimMontage* SkillAnim = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float STRRate = 1.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DEXRate = 1.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float INTRate = 1.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* StaticMesh = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USkeletalMesh* SkeletonMesh = nullptr;
};

USTRUCT(BlueprintType)
struct FItemObject : public FTableRowBase
{
    GENERATED_BODY()

    FItemObject();
    FItemObject(const FItemObject& Other)
    {
        ID = Other.ID;
        Name = Other.Name;
        ItemObject = Other.ItemObject;
    };

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 ID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Name = "Name";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class AEKItem_Base> ItemObject = nullptr;
};
