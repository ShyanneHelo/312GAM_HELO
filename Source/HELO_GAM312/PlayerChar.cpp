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

	//Set the size of the ResourcesArray to hold 3 elements (e.g., placeholders for resource counts or names)
	ResourcesArray.SetNum(3);

	//Add the names of the available resources to the ResourcesNameArray
	ResourcesNameArray.Add(TEXT("Wood"));
	ResourcesNameArray.Add(TEXT("Stone"));
	ResourcesNameArray.Add(TEXT("Berry"));



}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();

	//Sets a repeating timer to call DecreaseStats() every 2 seconds
	FTimerHandle StatsTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, &APlayerChar::DecreaseStats, 2.0f, true);
	
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
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X); // Calculate forward direction based on the controller's rotation and move the character in that direction
	AddMovementInput(Direction, axisValue);
}

void APlayerChar::MoveRight(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y); // Calculate right direction based on the controller's rotation and move the character right/left
	AddMovementInput(Direction, axisValue);
}

void APlayerChar::StartJump()
{
	bPressedJump = true; // Trigger the character's jump by setting the jump flag to true
}

void APlayerChar::StopJump()
{
	bPressedJump = false; // Stop the character's jump by clearing the jump flag to false
}

void APlayerChar::FindObject()
{
	
	FHitResult HitResult;  //Stores information about the result of a line trace (hit detection)
	FVector StartLocation = PlayerCamComp->GetComponentLocation(); //Get the starting point of the line trace from the player's camera location
	FVector Direction = PlayerCamComp->GetForwardVector() * 800.0f; //Get the forward direction from the player's camera and multiply by 800 units for trace distance
	FVector EndLocation = StartLocation + Direction; //Calculate the end point of the line trace by adding the direction to the start location
	
	FCollisionQueryParams QueryParams; //Create a collision query parameter object to configure the line trace behavior
	QueryParams.AddIgnoredActor(this); //Ignore the actor that owns this code (usually the player) to prevent self-collision during the trace
	QueryParams.bTraceComplex = true; //Enable complex collision checking (uses triangle meshes instead of simple collision shapes)
	QueryParams.bReturnFaceIndex = true; //Return the face index of the triangle that was hit (useful for advanced hit detection or effects)


	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams)) //Perform a line trace (raycast) from the player's camera forward to detect visible objects
	{
		AResource_M* HitResource = Cast<AResource_M>(HitResult.GetActor()); //Try to cast the hit actor to a resource object (AResource_M)

		if (Stamina > 5.0f)
		{

			if (HitResource) 
			{
				FString hitName = HitResource->resourceName; //Get the name of the resource hit
				int resourceValue = HitResource->resourceAmount; // Get how much of the resource is available to collect 

				HitResource->totalResource = HitResource->totalResource - resourceValue; //Subtract the collected amount from the total available resource

				if (HitResource->totalResource > resourceValue)  //If the resource still has more than the collectible amount, give it to the player
				{
					GiveResource(resourceValue, hitName); //Add the resource to the player's inventory

					check(GEngine != nullptr);  //Ensure GEngine is valid before trying to display a debug message
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Collected")); //Display a debug message on screen indicating resource collection

					UGameplayStatics::SpawnDecalAtLocation(GetWorld(), hitDecal, FVector(10.0f, 10.0f, 10.0f), HitResult.Location, FRotator(-90, 0, 0), 2.0f);  //Spawn a decal at the hit location (e.g., a visual mark on the surface that was hit)

					SetStamina(-5.0f);  //Reduce the player's stamina by 5 when performing the action (e.g., harvesting)

				}
				else  //If the resource has been fully collected or is below the collectible amount
				{
					HitResource->Destroy();  //Remove the resource actor from the world
					check(GEngine != nullptr);  //Ensure the engine exists before displaying a debug message
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted")); //Display a debug message on screen indicating the resource is depleted

				}
			}
		}
	}
}

//sets the players health ensuring it doesnt exceed 100
void APlayerChar::SetHealth(float amount)
{
	if (Health + amount < 100)
	{
		Health = Health + amount;
	}
}

//sets the players hungers ensuring it doesnt exceed 100
void APlayerChar::SetHunger(float amount)
{
	if (Hunger + amount < 100)
	{
		Hunger = Hunger + amount;
	}

}

//sets the players stamina ensuring it doesnt exceed 100
void APlayerChar::SetStamina(float amount)
{
	if (Stamina + amount <= 100)
	{
		Stamina = Stamina + amount;
	}
}

//called periodically to reduce stats over time and simulate survival mechanics
void APlayerChar::DecreaseStats()
{
	//decrease hunger by 1 if there is any hunger left
	if (Hunger > 0)
	{
		SetHunger(-1.0f);
	}
	
	//restore stamina by 10 every cycle
	SetStamina(10.0f);

	//if hunger has delpleted, reduce health to simulate starvation 
	if (Hunger <= 0)
	{
		SetHealth(-3.0f);
	}
}

void APlayerChar::GiveResource(float amount, FString resourceType)
{
	if (resourceType == "Wood")  //Add amount to the corresponding resource in ResourcesArray based on the type
	{
		ResourcesArray[0] = ResourcesArray[0] + amount;  //Index 0 = Wood
	}

	if (resourceType == "Stone")
	{
		ResourcesArray[1] = ResourcesArray[1] + amount; //Index 1 = Stone
	}

	if (resourceType == "Berry")
	{
		ResourcesArray[2] = ResourcesArray[2] + amount; //Index 2 = Berry
	}
}

