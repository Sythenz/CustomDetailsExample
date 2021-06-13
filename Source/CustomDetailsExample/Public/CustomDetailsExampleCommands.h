// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CustomDetailsExampleStyle.h"

class FCustomDetailsExampleCommands : public TCommands<FCustomDetailsExampleCommands>
{
public:

	FCustomDetailsExampleCommands()
		: TCommands<FCustomDetailsExampleCommands>(TEXT("CustomDetailsExample"), NSLOCTEXT("Contexts", "CustomDetailsExample", "CustomDetailsExample Plugin"), NAME_None, FCustomDetailsExampleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};