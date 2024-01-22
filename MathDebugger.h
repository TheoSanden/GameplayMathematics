// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MathDebugger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MATH_API UMathDebugger : public USceneComponent
{
	GENERATED_BODY()



public:	
	// Sets default values for this component's properties
	UMathDebugger();
	TArray<AActor*> DebugBoxes;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Values")
	float ViewConeHalfAngle = 180;
	UPROPERTY(EditAnywhere, Category = "Values")
	float ViewDistance = 10;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DrawViewCone(FColor color,float deltaTime);
	void DrawCircleArc(FColor color, int segments, float angle, float radius,float deltaTime);
	bool CheckIfAnyBoxInView();
		
};
