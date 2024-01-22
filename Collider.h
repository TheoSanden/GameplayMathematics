// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "MathUtil.h"
#include "Collider.generated.h"

UENUM(BlueprintType)
enum class EIntersectionType : uint8 {
	None       UMETA(DisplayName="None"),
	Sphere      UMETA(DisplayName="Sphere"),
	AABB        UMETA(DisplayName="AABB"),
	Plane		UMETA(DisplayName = "Plane")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MATH_API UCollider : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollider();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	EIntersectionType Type;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	EIntersectionType GetType();
	virtual void DrawDebugShape(FColor Color, float DeltaTime);
};
