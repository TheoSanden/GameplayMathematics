// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaneCollider.h"

UPlaneCollider::UPlaneCollider()
{
	Type = EIntersectionType::Plane;
}

FVector UPlaneCollider::GetNormal()
{
	return Normal.Vector();
}

void UPlaneCollider::DrawDebugShape(FColor Color, float DeltaTime)
{
	Super::DrawDebugShape(Color, DeltaTime);
	FPlane plane = FPlane(GetComponentLocation(),GetNormal());
	DrawDebugSolidPlane(GetWorld(),plane,GetComponentLocation(),DebugSize,Color,false,DeltaTime);
	 
}
