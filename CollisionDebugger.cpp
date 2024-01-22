// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionDebugger.h"

#include "CollisionHelpers.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
UCollisionDebugger::UCollisionDebugger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

void UCollisionDebugger::HandleCollision(float DeltaTime)
{
	bool Collision = false;
	for (UCollider* Col : colliders)
	{
		for (UCollider* Other : colliders)
		{
			if (Col == Other) { continue; }
			Collision = false;
			switch (Col->GetType())
			{
			case EIntersectionType::None:
				break;
			case EIntersectionType::Sphere:
				switch (Other->GetType())
				{
				case EIntersectionType::None:
					break;
				case EIntersectionType::Sphere:
					Collision = UCollisionHelpers::SphereSphereIntersection(
						Cast<USphereCollider>(Col), Cast<USphereCollider>(Other));
					break;
				case EIntersectionType::AABB:
					Collision = UCollisionHelpers::SphereAABBIntersection(
						Cast<USphereCollider>(Col), Cast<UAABBCollider>(Other));
					break;
				case EIntersectionType::Plane:
					Collision = UCollisionHelpers::SpherePlaneIntersection(
						Cast<USphereCollider>(Col), Cast<UPlaneCollider>(Other));
					break;
				}
				break;
			case EIntersectionType::AABB:
				switch (Other->GetType())
				{
				case EIntersectionType::None:
					break;
				case EIntersectionType::Sphere:
					Collision = UCollisionHelpers::SphereAABBIntersection(
						Cast<USphereCollider>(Other), Cast<UAABBCollider>(Col));
					break;
				case EIntersectionType::AABB:
					Collision = UCollisionHelpers::AABBIntersection(Cast<UAABBCollider>(Col),
					                                                Cast<UAABBCollider>(Other));
					break;
				case EIntersectionType::Plane: break;
				}
				break;
			case EIntersectionType::Plane:
				switch (Other->GetType())
				{
				case EIntersectionType::None:
					break;
				case EIntersectionType::Sphere:
					Collision = UCollisionHelpers::SpherePlaneIntersection(
						Cast<USphereCollider>(Other), Cast<UPlaneCollider>(Col));
					break;
				case EIntersectionType::AABB: break;
				case EIntersectionType::Plane: break;
				}
			}
			if (!IntersectionMap[Col] && Collision)
			{
				IntersectionMap[Col] = true;
			}
			if (!IntersectionMap[Other] && Collision)
			{
				IntersectionMap[Other] = true;
			}
		}
	}
	for (auto var : IntersectionMap)
	{
		const FColor color = (var.Value) ? FColor::Green : FColor::Red;
		var.Key->DrawDebugShape(color, DeltaTime);
		IntersectionMap[var.Key] = false;
	}
}

void UCollisionDebugger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleCollision(DeltaTime);
}

void UCollisionDebugger::RegisterCollider(UCollider* collider)
{
	colliders.Add(collider);
	IntersectionMap.Add(collider, false);
}

void UCollisionDebugger::DeRegisterCollider(UCollider* collider)
{
	colliders.Remove(collider);
	IntersectionMap.Add(collider, true);
}

TStatId UCollisionDebugger::GetStatId() const
{
	return GetStatID();
}

bool UCollisionDebugger::LinePlaneIntersection(FVector Origin, FVector Direction, bool IsInfinite)
{
	FColor Color = FColor::Red;
	bool Collision = false;
	for (UCollider* col : colliders)
	{
		if(col->GetType() == EIntersectionType::Plane)
		{
			 Collision = UCollisionHelpers::LinePlaneIntersection(Origin,Direction, Cast<UPlaneCollider>(col),IsInfinite);
			

			if(Collision)
			{
				Color = FColor::Green;
				break;
			}
		}
	}
	DrawDebugLine(GetWorld(),Origin,Origin + Direction, Color,false, GetWorld()->GetDeltaSeconds() * 2);
	return false;
}

// Called when the game starts or when spawned
/*void ACollisionDebugger::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> DebugActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),FName("Debug"), DebugActors);

	UE_LOG(LogTemp,Warning,TEXT("Actors Found: %f"),DebugActors.Num());
	for (AActor* actor : DebugActors)
	{
		TArray<UCollider*> collidersComponent;
		actor->GetComponents<UCollider>(collidersComponent);
		UE_LOG(LogTemp,Warning,TEXT("CollidersFound: %f"),collidersComponent.Num());
		if (colliders.Num() != 0)
		{
			colliders.Add(collidersComponent[0]);
		}
	}
}*/
