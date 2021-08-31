// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UeJameGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UEJAM2021_API UUeJameGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		int32 CurrentLevel = 1;

	
	
};
