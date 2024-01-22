// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpatialBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MATH_API USpatialBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Spatial)
	static bool IsBehind(AActor* source, AActor* target);
	UFUNCTION(BlueprintCallable, Category = Spatial)
	static bool IsInFront(AActor* source, AActor* target);
	UFUNCTION(BlueprintCallable, Category = Spatial)
	static bool IsToTheRight(AActor* source, AActor* target);
	UFUNCTION(BlueprintCallable, Category = Spatial)
	static bool IsToTheLeft(AActor* source, AActor* target);
	UFUNCTION(BlueprintCallable, Category = Spatial)
	static bool InView(AActor* source, AActor* target, float HalfAngle, float ViewDistance);
	UFUNCTION(BlueprintCallable, Category = Spatial)
	static FString GetContext(AActor* source, AActor* target);
private: 
	//return the position of the target relative to the source 
	static FVector GetLocalizedLocation(AActor* source, AActor* target);
	
};
