// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
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


};
