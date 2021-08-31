// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/DataTable.h"
#include "UeJam2021GameMode.generated.h"

UCLASS(minimalapi)
class AUeJam2021GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUeJam2021GameMode();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		int32 CurrentLevel = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		bool LevelDestroid = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		UDataTable* LevelData;

	UFUNCTION(BlueprintCallable, Category = "Level")
		FString GetRowLevelName(FString RowNumber);
	UFUNCTION(BlueprintCallable, Category = "Level")
		void loadNextLevel();
	UFUNCTION(BlueprintCallable, Category = "Level")
		void loadSpecificLevel(FString row);
	UFUNCTION(BlueprintCallable, Category = "Level")
		void ResetCurrentLevel();
};



