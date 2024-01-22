// Fill out your copyright notice in the Description page of Project Settings.


#include "AABBCollider.h"
#include  "DrawDebugHelpers.h"
// Sets default values for this component's properties
UAABBCollider::UAABBCollider()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Type = EIntersectionType::AABB;
	// ...
}

FVector UAABBCollider::GetExtents()
{
	return Extents;
}

FVector UAABBCollider::GetWorldMinExtents()
{
	return GetComponentLocation() - Extents;
}

FVector UAABBCollider::GetWorldMaxExtents()
{
	return GetComponentLocation() + Extents;
}


// Called when the game starts
void UAABBCollider::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UAABBCollider::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

}

void UAABBCollider::DrawDebugShape(FColor Color, float DeltaTime)
{
	UWorld* world = GetWorld();
	FVector pos = GetComponentLocation();
	DrawDebugBox(world,pos,Extents,Color,false,DeltaTime);
}

