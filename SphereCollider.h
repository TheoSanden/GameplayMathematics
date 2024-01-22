// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collider.h"
#include "Components/SceneComponent.h"
#include "SphereCollider.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MATH_API USphereCollider :public UCollider
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USphereCollider();

	UPROPERTY(EditDefaultsOnly)
	float Radius;

	float GetRadius();


protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void DrawDebugShape(FColor Color, float DeltaTime) override;
		
};
