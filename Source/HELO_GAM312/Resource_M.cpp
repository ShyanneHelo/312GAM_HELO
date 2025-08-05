// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_M.h"

// Sets default values
AResource_M::AResource_M()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the text render component to display the resource's name in the world
	ResourceNameTxt = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render"));

	//Create the static mesh component to visually represent the resource
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	//Set the static mesh as the root component of the actor
	RootComponent = Mesh;

	// Attach the text render component to the mesh so it moves with it
	ResourceNameTxt->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AResource_M::BeginPlay()
{
	Super::BeginPlay();

	//Convert the resource name (FString) to FText for UI display
	tempText = tempText.FromString(resourceName);

	//Set the text render component to display the resource's name
	ResourceNameTxt->SetText(tempText);
	
}

// Called every frame
void AResource_M::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

