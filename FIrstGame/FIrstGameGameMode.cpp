// Copyright Epic Games, Inc. All Rights Reserved.

#include "FIrstGameGameMode.h"
#include "FIrstGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFIrstGameGameMode::AFIrstGameGameMode()
{
	// set default pawn class to our Blueprinted character
/*	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Class'/Script/FIrstGame.FirstPawn'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	*/
}
