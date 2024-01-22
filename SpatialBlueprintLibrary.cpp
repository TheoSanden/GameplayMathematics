// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialBlueprintLibrary.h"

bool USpatialBlueprintLibrary::IsBehind(AActor* source, AActor* target)
{
	return GetLocalizedLocation(source,target).X > 0;
}

bool USpatialBlueprintLibrary::IsInFront(AActor* source, AActor* target)
{
	return GetLocalizedLocation(source, target).X < 0;
}

bool USpatialBlueprintLibrary::IsToTheRight(AActor* source, AActor* target)
{
	return GetLocalizedLocation(source, target).Y > 0;
}

bool USpatialBlueprintLibrary::IsToTheLeft(AActor* source, AActor* target)
{
	return GetLocalizedLocation(source, target).Y < 0;
}
FString USpatialBlueprintLibrary::GetContext(AActor* source, AActor* target)
{
	FString context = "";
	FString infront = FString("Front: ") + ((IsInFront(source,target))? "True": "False");
	FString behind = FString("| Behind : ") + ((IsBehind(source,target))? "True": "False");
	FString right = FString("| Right : ") + ((IsToTheLeft(source,target))? "True": "False");
	FString left = FString("| Left: ") + ((IsToTheRight(source,target))? "True": "False");

	context = infront + behind + right + left;
	return context;
}

bool USpatialBlueprintLibrary::InView(AActor* source, AActor* target, float HalfAngle, float ViewDistance)
{
	FVector sourceToTarget = (target->GetActorLocation() - source->GetActorLocation());

	float dot = source->GetActorForwardVector().Dot(sourceToTarget.GetSafeNormal());

	float convertedHalfAngle = 1 - (FMath::Clamp(HalfAngle,0,180)/360) *4;

	if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Converted Half angle: %f"), convertedHalfAngle));

	return (dot > convertedHalfAngle) && (sourceToTarget.Length() <= ViewDistance);
}

FVector USpatialBlueprintLibrary::GetLocalizedLocation(AActor* source, AActor* target)
{
	return source->GetTransform().InverseTransformPosition(target->GetActorLocation());
}
