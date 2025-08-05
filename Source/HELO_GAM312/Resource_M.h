// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Resource_M.generated.h"


UCLASS()
class HELO_GAM312_API AResource_M : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResource_M();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Name of the resource (e.g., "Wood", "Stone", etc.)
	UPROPERTY(EditAnywhere)
	FString resourceName = "Wood";

	//Amount of this resource currently available (e.g., how much the player can collect)
	UPROPERTY(EditAnywhere)
	int resourceAmount = 5;

	//Maximum or total amount of the resource that exists in the environment or object
	UPROPERTY(EditAnywhere)
	int totalResource = 100;
	
	//Temporary display text used for rendering resource information (e.g., for UI or debugging)
	UPROPERTY()
	FText tempText;

	//Text component used to display the resource name in the game world
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* ResourceNameTxt;

	//Static mesh component that represents the physical object of the resource in the world
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;



};
