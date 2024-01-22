// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AABBCollider.h"
#include "PlaneCollider.h"
#include "SphereCollider.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CollisionHelpers.generated.h"

/**
 * 
 */
UCLASS()
class MATH_API UCollisionHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static bool SphereSphereIntersection(USphereCollider* a, USphereCollider* b);
	static bool SphereAABBIntersection(USphereCollider* a, UAABBCollider* b);
	static bool AABBIntersection(UAABBCollider* a, UAABBCollider* b);
	static bool SpherePlaneIntersection(USphereCollider* a, UPlaneCollider* b);
	static bool LinePlaneIntersection(FVector origin,FVector Direction, UPlaneCollider* plane, bool IsInfinite);

	UFUNCTION(BlueprintCallable)
	static bool LineCastToPlanesInScene(AActor* instigator, FVector origin, FVector Direction, bool IsInfinite);
};
