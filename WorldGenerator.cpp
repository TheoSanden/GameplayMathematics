// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGenerator.h"
#include "KismetProceduralMeshLibrary.h"
#include "NoiseHelpers.h"

// Sets default values
AWorldGenerator::AWorldGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh");
	ProceduralMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWorldGenerator::BeginPlay()
{
	Super::BeginPlay();
	GenerateVertices();
	GenerateTriangles();
	GenerateHeightMaps();
	ModifyVertices();
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;
	//UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices,Triangles,UV,Normals,Tangents);
	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, Normals,UV,TArray<FColor>(),Tangents,true);
	ProceduralMesh->UpdateMeshSection(0,Vertices, Normals,UV,TArray<FColor>(),Tangents);
	
}

// Called every frame
void AWorldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldGenerator::GenerateVertices()
{
	float VertexOffset = MeshScale/Fidelity;
	for (int x = 0; x < Fidelity; x++)
	{
		for (int y = 0; y < Fidelity; y++)
		{
			Vertices.Add(FVector(x*VertexOffset,y*VertexOffset,0));
			UV.Add(FVector2D((float)x/Fidelity,(float)y/Fidelity));
		}		
	}
}

void AWorldGenerator::GenerateTriangles()
{
	if(Vertices.Num() == 0){return;}
	for(int i = 0; i < Vertices.Num() - Fidelity; i++)
	{
		if(i != 0 && (i + 1) % (Fidelity) == 0){continue;}
		
		Triangles.Add(i);
		Triangles.Add(i + Fidelity + 1);
		Triangles.Add(i + Fidelity );

		Triangles.Add(i);
		Triangles.Add(i  +1);
		Triangles.Add(i + Fidelity + 1);
	}
}

void AWorldGenerator::GenerateHeightMaps()
{
	HeightMap = UNoiseHelpers::Perlin(Fidelity,Fidelity,TextureScale,Octaves,Persistence,Lacunarity);
	UTexture* Texuture = UNoiseHelpers::GenerateHeightMap(HeightMap, Fidelity, FString("ProcMeshHeightMap"));
}

void AWorldGenerator::ModifyVertices()
{
	for(int x = 0; x < Fidelity; x++)
	{
		for(int y = 0; y < Fidelity; y++)
		{
			Vertices[y * Fidelity + x] +=  FVector::UpVector * UKismetMathLibrary::Ease(0,1,HeightMap[y * Fidelity + x],HeightEasing) * MaxHeight;
		}
	}
}

