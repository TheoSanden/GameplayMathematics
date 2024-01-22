// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionHelpers.h"

#include "CollisionDebugger.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

bool UCollisionHelpers::SphereSphereIntersection(USphereCollider* a, USphereCollider* b)
{
	float Distance = (a->GetComponentLocation() - b->GetComponentLocation()).Length();
	float Diameter = a->GetRadius() + b->GetRadius();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green,
	                                 FString::Printf(TEXT("Distance Betweem Collider: %f"), Distance));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Compounded Radius: %f"), Diameter));
	FString collision = (Distance <= (Diameter)) ? "True" : "False";
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Collision: %s"), *collision));
	return (Distance <= (Diameter));
}

bool UCollisionHelpers::SphereAABBIntersection(USphereCollider* a, UAABBCollider* b)
{
	FVector aPos = a->GetComponentLocation();
	FVector bPos = b->GetComponentLocation();
	FVector extents = b->GetExtents();

	FVector SphereIntersectionPoint = aPos + (bPos - aPos).GetSafeNormal() * a->Radius;
	SphereIntersectionPoint = UKismetMathLibrary::InverseTransformLocation(
		b->GetComponentTransform(), SphereIntersectionPoint);

	const bool inX = (SphereIntersectionPoint.X < extents.X && SphereIntersectionPoint.X > -extents.X);
	const bool inY = (SphereIntersectionPoint.Y < extents.Y && SphereIntersectionPoint.Y > -extents.Y);
	const bool inZ = (SphereIntersectionPoint.Z < extents.Z && SphereIntersectionPoint.Z > -extents.Z);

	return inX && inY && inZ;
}

bool UCollisionHelpers::AABBIntersection(UAABBCollider* a, UAABBCollider* b)
{
	FVector AeMax = a->GetWorldMaxExtents();
	FVector AeMin = a->GetWorldMinExtents();
	FVector BeMax = b->GetWorldMaxExtents();
	FVector BeMin = b->GetWorldMinExtents();
	return (
		AeMin.X <= BeMax.X &&
		AeMax.X >= BeMin.X&&
		AeMin.Y <= BeMax.Y &&
		AeMax.Y >= BeMin.Y &&
		AeMin.Z <= BeMax.Z &&
		AeMax.Z >= BeMin.Z
	);
}

bool UCollisionHelpers::SpherePlaneIntersection(USphereCollider* a, UPlaneCollider* b)
{
	FVector bToA =  a->GetComponentLocation()- b->GetComponentLocation();
	float DotProj = b->GetNormal().Dot(bToA);
	FVector projectedPoint = a->GetComponentLocation() - DotProj * b->GetNormal();
	return (projectedPoint - a->GetComponentLocation()).Length() < a->GetRadius();
}

bool UCollisionHelpers::LinePlaneIntersection(FVector origin, FVector Direction, UPlaneCollider* plane, bool IsInfinite = false)
{
	FVector PlaneNormal = plane->GetNormal();
	FVector PlaneOrigin = plane->GetComponentLocation();
	FVector PlaneToOriginNormal = (origin - PlaneOrigin).GetSafeNormal(); 
	bool Behind = (PlaneNormal.Dot(PlaneToOriginNormal) < 0);

	bool InfiniteCollision = (Behind && PlaneNormal.Dot(Direction.GetSafeNormal()) > 0)? true: (!Behind && PlaneNormal.Dot(Direction.GetSafeNormal())< 0)? true: false;

	if(!InfiniteCollision){return false;}
	
	FVector VerticalProjection = PlaneNormal * PlaneNormal.Dot(PlaneOrigin - origin);
	FVector UnscaledVerticalProjection = PlaneNormal * PlaneNormal.Dot(Direction);
	FVector UnscaledHorizontal = Direction - UnscaledVerticalProjection;
	float ScaleMultiplier = VerticalProjection.Length()/ UnscaledVerticalProjection.Length();
	FVector Horizontal =  UnscaledHorizontal * ScaleMultiplier;
	FVector OriginPlaneIntersection = origin + VerticalProjection;
	FVector DirectionPlaneIntersection =  OriginPlaneIntersection + Horizontal;

	DrawDebugPoint(plane->GetWorld(),DirectionPlaneIntersection,5,FColor::Blue,false, plane->GetWorld()->GetDeltaSeconds()*2);
	
	if(IsInfinite){return InfiniteCollision;}
	if(!IsInfinite && !InfiniteCollision){return false;}
	
	
	return (DirectionPlaneIntersection - origin).Length() < Direction.Length(); 
	
}

bool UCollisionHelpers::LineCastToPlanesInScene(AActor* instigator, FVector origin, FVector Direction, bool IsInfinite)
{
	UCollisionDebugger* Debugger = instigator->GetWorld()->GetSubsystem<UCollisionDebugger>();
	return Debugger->LinePlaneIntersection(origin,Direction,IsInfinite);
}
