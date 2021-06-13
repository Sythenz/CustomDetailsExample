// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CustomDetailsExample.h"
#include "CustomDetailsExampleStyle.h"
#include "CustomDetailsExampleCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "PropertyEditorModule.h"
#include "CustomSettings.h"

static const FName CustomDetailsExampleTabName("CustomDetailsExample");

#define LOCTEXT_NAMESPACE "FCustomDetailsExampleModule"

void FCustomDetailsExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FCustomDetailsExampleStyle::Initialize();
	FCustomDetailsExampleStyle::ReloadTextures();

	FCustomDetailsExampleCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCustomDetailsExampleCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FCustomDetailsExampleModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FCustomDetailsExampleModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FCustomDetailsExampleModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CustomDetailsExampleTabName, FOnSpawnTab::CreateRaw(this, &FCustomDetailsExampleModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FCustomDetailsExampleTabTitle", "CustomDetailsExample"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

}

void FCustomDetailsExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FCustomDetailsExampleStyle::Shutdown();

	FCustomDetailsExampleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CustomDetailsExampleTabName);
}

TSharedRef<SDockTab> FCustomDetailsExampleModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	//Create our Details Panel object
	CustomSettings = NewObject<UCustomSettings>();

	//Load our Property Module
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//FDetailsViewArgs is a struct of settings to customize our Details View Widget
	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;

	//Create the widget and store it in the PropertyWidget pointer
	PropertyWidget = PropertyModule.CreateDetailView(Args);

	//Important! We set our details view to use our Custom Settings object
	PropertyWidget->SetObject(CustomSettings);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			PropertyWidget.ToSharedRef()
		];
}

void FCustomDetailsExampleModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(CustomDetailsExampleTabName);
}

void FCustomDetailsExampleModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FCustomDetailsExampleCommands::Get().OpenPluginWindow);
}

void FCustomDetailsExampleModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FCustomDetailsExampleCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomDetailsExampleModule, CustomDetailsExample)