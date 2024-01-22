// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collider.h"
#include "PlaneCollider.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MATH_API UPlaneCollider : public UCollider
{
	GENERATED_BODY()
public:
	UPlaneCollider();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRotator Normal;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DebugSize = 100;
public:
	FVector GetNormal();
	virtual void DrawDebugShape(FColor Color, float DeltaTime) override;
};
