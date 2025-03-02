// Copyright Epic Games, Inc. All Rights Reserved.

#include "BehaviorTreeGameMode.h"
#include "BehaviorTreeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABehaviorTreeGameMode::ABehaviorTreeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
