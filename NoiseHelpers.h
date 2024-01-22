// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NoiseHelpers.generated.h"

/**
 * 
 */
UCLASS()
class MATH_API UNoiseHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static TArray<float> Perlin(int MapWidth,int MapHeight, float Scale,int Octaves, float Persistence, float Lacunarity);
	static float InverseLerp(float xx, float yy, float value);
	static UTexture2D* GenerateHeightMap(TArray<float> HeightValues,int TextureWidth, FString Name); 
};
