// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class HELO_GAM312_API UObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void UpdatematOBJ(float matsCollected); // Blueprint-implementable event to update the material collection objective UI or logic

	UFUNCTION(BlueprintImplementableEvent)
	void UpdatebuildOBJ(float objectsBuilt);  // Blueprint-implementable event to update the object building objective UI or logic
};
