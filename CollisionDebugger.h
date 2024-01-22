// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collider.h"
#include "GameFramework/Actor.h"
#include "CollisionDebugger.generated.h"

UCLASS()
class MATH_API UCollisionDebugger : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	TSet<UCollider*> colliders;
	TMap<UCollider*,bool> IntersectionMap;
public:	
	// Sets default values for this actor's properties
	UCollisionDebugger();

	
protected:
	
	void HandleCollision(float DeltaTime);
	// Called when the game starts or when spawned
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RegisterCollider(UCollider* collider);
	void DeRegisterCollider(UCollider* collider);
	virtual TStatId GetStatId() const override;

	bool LinePlaneIntersection(FVector Origin, FVector Direction, bool IsInfinite = false);

};
