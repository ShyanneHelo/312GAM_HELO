// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initial setup of Camera Component. 
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Cam"));

	//Attachment of the camera to the character mesh and head bone.
	PlayerCamComp->SetupAttachment(GetMesh(), "head");

	//Share rotation with controller
	PlayerCamComp->bUsePawnControlRotation = true;


}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Bind player input to movement, camera controls, and gameplay actions.
	//Axis binding handle continous input (e.g. Movement, mouse look).
	//Action bindings handle discrete events (e.g Jump, Interact)
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerChar::MoveForward); //Move character forward and backward
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerChar::MoveRight);   //Move Character Right and Left
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerChar::AddControllerPitchInput);  //Look up and down with mouse
	PlayerInputComponent->BindAxis("Turn", this, &APlayerChar::AddControllerYawInput);  //turn left or right with mouse
	PlayerInputComponent->BindAction("JumpEvent", IE_Pressed, this, &APlayerChar::StartJump); //start jump on press
	PlayerInputComponent->BindAction("JumpEvent", IE_Released, this, &APlayerChar::StopJump); //stop jump on release

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerChar::FindObject);  //Find object on press
	
}

void APlayerChar::MoveForward(float axisValue)
{
	// Calculate forward direction based on the controller's rotation and move the character in that direction
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, axisValue);
}

void APlayerChar::MoveRight(float axisValue)
{
	// Calculate right direction based on the controller's rotation and move the character right/left
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, axisValue);
}

void APlayerChar::StartJump()
{
	// Trigger the character's jump by setting the jump flag to true
	bPressedJump = true;
}

void APlayerChar::StopJump()
{
	// Stop the character's jump by clearing the jump flag to false
	bPressedJump = false;
}

void APlayerChar::FindObject()
{
}

