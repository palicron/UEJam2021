// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FLevelList: public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    FLevelList(): LevelName(""), LevelUnlock(false){}
	;

 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
        FString LevelName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
        bool LevelUnlock;
};


/**
 * 
 */
UCLASS()
class UEJAM2021_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static FVector GetLaunchForceHorizontal(FVector direction, FVector Velocity, float HorizontalDistan, float Mass,float DashVelocity,float time);
};
