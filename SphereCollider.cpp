// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereCollider.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USphereCollider::USphereCollider()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Type = EIntersectionType::Sphere;
	// ...
}

float USphereCollider::GetRadius()
{
	return Radius;
}


// Called when the game starts
/*void USphereCollider::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}*/


// Called every frame
void USphereCollider::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// ...
}

void USphereCollider::DrawDebugShape(FColor Color, float DeltaTime)
{
	DrawDebugSphere(GetWorld(),GetComponentLocation(),Radius,16, Color,false,DeltaTime);
}

