// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomSettings.generated.h"
/*
*
*/
UCLASS(BlueprintType, config = EditorPerProjectUserSettings)
class CUSTOMDETAILSEXAMPLE_API UCustomSettings : public UObject
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, category="Custom Settings")
	UStaticMesh* CustomMesh;

	UPROPERTY(EditAnywhere, category = "Custom Settings")
	float CustomFloat;

	UPROPERTY(EditAnywhere, category = "Other Settings")
	bool CustomBool;
};
