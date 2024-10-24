// Copyright Epic Games, Inc. All Rights Reserved.

#include "ButterflyGameMode.h"
#include "ButterflyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AButterflyGameMode::AButterflyGameMode()
{
	

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
