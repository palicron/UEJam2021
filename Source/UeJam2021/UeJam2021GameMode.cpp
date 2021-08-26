// Copyright Epic Games, Inc. All Rights Reserved.

#include "UeJam2021GameMode.h"
#include "UeJam2021Character.h"
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
