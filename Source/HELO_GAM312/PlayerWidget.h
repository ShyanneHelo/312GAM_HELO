 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class HELO_GAM312_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBars(float Health1, float Hunger1, float Stamina1);  // Blueprint event that allows the UI to be updated with new health, hunger, and stamina vaules
};
