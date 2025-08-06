// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "BuildingPart.generated.h"

UCLASS()
class HELO_GAM312_API ABuildingPart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingPart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;  // Exposes the static mesh component in the editor for assignment or adjustment

	UPROPERTY(EditAnywhere)
	UArrowComponent* PivotArrow;  // Exposes the arrow component in the editor, typically used as a directional or pivot reference

};
