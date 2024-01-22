// Fill out your copyright notice in the Description page of Project Settings.


#include "Collider.h"

#include "CollisionDebugger.h"

// Sets default values for this component's properties
UCollider::UCollider()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCollider::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetSubsystem<UCollisionDebugger>()->RegisterCollider(this);
	// ...
}


// Called every frame
void UCollider::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EIntersectionType UCollider::GetType()
{
	return Type;
}

void UCollider::DrawDebugShape(FColor Color, float DeltaTime)
{
}

