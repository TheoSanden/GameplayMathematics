// Fill out your copyright notice in the Description page of Project Settings.


#include "MathDebugger.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SpatialBlueprintLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UMathDebugger::UMathDebugger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMathDebugger::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),FName("Debug"), DebugBoxes);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Amount of boxes found: %f"), DebugBoxes.Num()));
	
}


// Called every frame
void UMathDebugger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawViewCone(CheckIfAnyBoxInView()? FColor::Green:FColor:: Red, DeltaTime);
	// ...
}


void UMathDebugger::DrawViewCone(FColor color, float deltaTime)
{
	float rad = FMath::DegreesToRadians(ViewConeHalfAngle);
	DrawCircleArc(color,64,ViewConeHalfAngle * 2,ViewDistance,deltaTime);

	float x = FMath::Sin(rad);
	float y = FMath::Cos(rad);

	FVector leftEdge = FVector(y,-x,0) * ViewDistance;
	FVector rightEdge = FVector(y, x, 0) * ViewDistance;


	leftEdge = UKismetMathLibrary::TransformDirection(GetOwner()->GetTransform(),leftEdge);
	rightEdge = UKismetMathLibrary::TransformDirection(GetOwner()->GetTransform(), rightEdge);

	FVector start = GetOwner()->GetActorLocation();

	DrawDebugLine(GetWorld(),start,start + leftEdge, color,false, deltaTime * 2);
	DrawDebugLine(GetWorld(), start, start + rightEdge, color, false, deltaTime * 2);
}

void UMathDebugger::DrawCircleArc(FColor color, int segments,float angle, float radius,float deltaTime)
{
	const UWorld* world = GetWorld();
	FTransform transform = GetOwner()->GetTransform();
	FVector actorWorldLocation = GetOwner()->GetActorLocation();
	FVector localStart;
	FVector localEnd;
	FVector start;
	FVector end;
	float rad = FMath::DegreesToRadians(angle);

	float arcLength = (rad / (float)segments);

	for(int i = 0; i < segments; i++)
	{
		localStart = FVector(FMath::Cos(-rad/2 + arcLength * i), -FMath::Sin(-rad/2 + arcLength * i),0);
		localEnd = FVector(FMath::Cos(-rad / 2 + arcLength * (i+1)), -FMath::Sin(-rad / 2 + arcLength * (i + 1)), 0);

		localStart = UKismetMathLibrary::TransformDirection(transform, localStart) * radius;
		localEnd = UKismetMathLibrary::TransformDirection(transform, localEnd) * radius;
		start = actorWorldLocation + localStart;
		end = actorWorldLocation + localEnd;

		DrawDebugLine(world,start,end, color,false,deltaTime);
	}
}

bool UMathDebugger::CheckIfAnyBoxInView()
{
	for(AActor* other : DebugBoxes)
	{
		if (other == GetOwner()) { continue; }
		if(USpatialBlueprintLibrary::InView(GetOwner(),other,ViewConeHalfAngle,ViewDistance))
		{
			/*if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Checking: %s"), *other->GetName()));*/

			return true;
		}
	}
	return false;
}

