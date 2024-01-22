// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collider.h"
#include "Components/SceneComponent.h"
#include "AABBCollider.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MATH_API UAABBCollider : public UCollider
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FVector Extents;
	TArray<FVector> LocalPoints;

public:	
	// Sets default values for this component's properties
	UAABBCollider();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void DrawDebugShape(FColor Color,float DeltaTime) override;
	FVector GetExtents();
	FVector GetWorldMinExtents();
	FVector GetWorldMaxExtents();
};
