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
        bUseable = Other.bUseable;
        StaticMesh = Other.StaticMesh;
        SkeletonMesh = Other.SkeletonMesh;
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
    bool bUseable = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USkeletalMesh* SkeletonMesh;
};
