// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
 	

#include "Kismet/KismetMathLibrary.h"
#include "ProceduralMeshComponent.h"
#include "WorldGenerator.generated.h"

USTRUCT()
struct FMyStruct
{
	GENERATED_BODY()
public:
	TArray<float> HeightMap;
	
};

UCLASS()
class MATH_API AWorldGenerator : public AActor
{
	GENERATED_BODY()
	float TextureSize = 256;
	
public:	
	// Sets default values for this actor's properties
	AWorldGenerator();
	UPROPERTY(EditAnywhere)
	TArray<float> HeightMap;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Fidelity;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MeshScale = 1000;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHeight = 1000;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TextureScale = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Persistence = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Lacunarity = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Octaves = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<EEasingFunc::Type> HeightEasing;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
	void GenerateVertices();
	void GenerateTriangles();
	void GenerateHeightMaps();
	void ModifyVertices();
	UPROPERTY(EditAnywhere)
	UProceduralMeshComponent* ProceduralMesh;
	UPROPERTY()
	TArray<FVector> Vertices;
	UPROPERTY()
	TArray<int> Triangles;
	UPROPERTY()
	TArray<FVector2D> UV;

};
