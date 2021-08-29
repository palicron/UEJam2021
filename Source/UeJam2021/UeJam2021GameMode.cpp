// Copyright Epic Games, Inc. All Rights Reserved.

#include "UeJam2021GameMode.h"
#include "UeJam2021Character.h"
#include "Kismet/GameplayStatics.h"
#include "MyBlueprintFunctionLibrary.h"
#include "UObject/ConstructorHelpers.h"

AUeJam2021GameMode::AUeJam2021GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

FString AUeJam2021GameMode::GetRowLevelName(FString RowNumber)
{
	if(LevelData)
	{
		FLevelList* result = LevelData->FindRow<FLevelList>(FName(*RowNumber), "");
	    if(result)
	    {
			return result->LevelName;
	    }
		else
		{
			return "";
		}

		
	}
	else
	{
		return "";
	}
}

void AUeJam2021GameMode::loadNextLevel()
{
	CurrentLevel++;
	FString name = GetRowLevelName(FString::FromInt(CurrentLevel));
	if(!name.IsEmpty())
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*name));
	}
	else
	{
		name = GetRowLevelName(FString::FromInt(1));
		UGameplayStatics::OpenLevel(GetWorld(), FName(*name));
	}
	
}

void AUeJam2021GameMode::loadSpecificLevel(FString row)
{

	FString name = GetRowLevelName(row);
	if (!name.IsEmpty())
	{
		CurrentLevel = FCString::Atoi(*row);
		UGameplayStatics::OpenLevel(GetWorld(), FName(*name));
	}
}
