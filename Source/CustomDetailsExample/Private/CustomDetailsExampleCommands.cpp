// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CustomDetailsExampleCommands.h"

#define LOCTEXT_NAMESPACE "FCustomDetailsExampleModule"

void FCustomDetailsExampleCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "CustomDetailsExample", "Bring up CustomDetailsExample window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
