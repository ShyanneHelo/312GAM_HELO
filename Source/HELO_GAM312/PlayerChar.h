// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Resource_M.h"
#include "Kismet/GameplayStatics.h"
#include "BuildingPart.h"
#include "PlayerWidget.h"
#include "PlayerChar.generated.h"

UCLASS()
class HELO_GAM312_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//handles forward and backward player movement input based on axis value.
	UFUNCTION()
	void MoveForward(float axisValue);

	//handles right and left player movement input based on axis value.
	UFUNCTION()
	void MoveRight(float axisValue);

	//called when the jump input is pressed; initiates the jump
	UFUNCTION()
	void StartJump();

	//called when the jump input is released; stops the jump
	UFUNCTION()
	void StopJump();

	//triggers the object-finding logic, such as interacting with nearby items
	UFUNCTION()
	void FindObject();

	//the players camera component, used to control the in-game viewpoint
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* PlayerCamComp;

	//Players current health value; decreases when taking damage and may affect survival 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health = 100.0f;
	
	//Players hunger level; can decrease over time and may impact stamina or health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Hunger = 100.0f;

	//Players stamina level; used for actions like sprinting or jumping, rebuilds overtime
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina = 100.0f;

	//Amount of wood the player has(used for crafting or building)
	UPROPERTY(EditAnywhere, Category = "Resources")
	int Wood;

	//Amount of stone the player has(used for crafting or building)
	UPROPERTY(EditAnywhere, Category = "Resources")
	int Stone;

	//Number of berries collected(could be used for eating or crafting)
	UPROPERTY(EditAnywhere, Category = "Resources")
	int Berry;

	//Array storing the actual list of resources the player has collected (e.g., "Wood", "Stone", "Berry")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TArray<int> ResourcesArray;

	//Array containing the names of available resources (e.g., "Wood", "Stone", "Berry")
	UPROPERTY(EditAnywhere, Category = "Resources")
	TArray<FString> ResourcesNameArray;

	UPROPERTY(EditAnywhere, Category = "HitMarker")
	UMaterialInterface* hitDecal;  //Material used to visually mark where a hit occurred (e.g., decal on surface)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Supplies")
	TArray<int> BuildingArray;  // Exposes an editable array of integers in the editor and Blueprints, categorized under "Building Supplies"

	UPROPERTY()
	bool isBuilding;  // A boolean flag to track whether the player is currently building; not exposed to editor or Blueprints

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ABuildingPart> BuildPartClass;  // Allows setting a default building part class (e.g., wall, floor) in the editor or Blueprints; cannot be changed at runtime

	UPROPERTY()
	ABuildingPart* spawnedPart;  // Pointer to the most recently spawned building part; hidden from editor and Blueprints

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerWidget* playerUI; // Reference to the player's UI widget

	//set the players health to a specfied amount
	UFUNCTION(BlueprintCallable)
	void SetHealth(float amount);

	//set the players hunger to a specified amount
	UFUNCTION(BlueprintCallable)
	void SetHunger(float amount);

	//set the players stamina to a specified amount
	UFUNCTION(BlueprintCallable)
	void SetStamina(float amount);

	//decreases the players stats overtime based on conditions (e.g. actions taken, time passed)
	UFUNCTION()
	void DecreaseStats();

	UFUNCTION()
	void GiveResource(float amount, FString resourceType);

	UFUNCTION(BlueprintCallable)
	void UpdateResources(float woodAmount, float stoneAmount, FString buildingObject); // Exposes this function to Blueprints, allowing you to update resource values from within BP scripts

	UFUNCTION(BlueprintCallable)
	void SpawnBuilding(int buildingID, bool& isSuccess); // Exposes this function to Blueprints; spawns a building by ID and returns success through a reference variable

	UFUNCTION()
	void RotateBuilding(); // Not exposed to Blueprints; rotates the current building (likely for internal logic or input events)


};

