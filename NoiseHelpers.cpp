// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseHelpers.h"

#include "IAutomationControllerManager.h"
#include "MathUtil.h"
#include "SAdvancedTransformInputBox.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Math/UnrealMathUtility.h"

TArray<float> UNoiseHelpers::Perlin(int MapWidth, int MapHeight, float Scale,int Octaves, float Persistence, float Lacunarity)
{
	float seed = FMath::GetRandSeed();
	TArray<float> noiseMap;
	noiseMap.Init(0,MapWidth * MapHeight);
	float XScaled;
	float YScaled;

	float MaxNoiseHeight = std::numeric_limits<float>::min();
	float MinNoiseHeight = std::numeric_limits<float>::max();
	
	for(int x = 0; x < MapWidth; x++)
	{
		for(int y = 0; y< MapHeight; y++)
		{
			float Amplitude = 1;
			float Frequency = 1;
			float NoiseHeight = 0;

			for(int i = 0; i < Octaves; i++)
			{
				XScaled = ((float)x/Scale * Frequency);
				YScaled = ((float)y/Scale * Frequency);
				float val = FMath::PerlinNoise2D(FVector2d(XScaled,YScaled)) * 2 -1;
				NoiseHeight += val * Amplitude;

				Amplitude *= Persistence;
				Frequency *= Lacunarity;
							
			}
			if(NoiseHeight > MaxNoiseHeight){MaxNoiseHeight = NoiseHeight;}
			else if(NoiseHeight < MinNoiseHeight){MinNoiseHeight = NoiseHeight;}
			noiseMap[y * MapWidth + x] = NoiseHeight;	
		}
	}

	for(int x = 0; x < MapHeight; x++)
	{
		for(int y = 0; y < MapHeight; y++)
		{
			noiseMap[y * MapWidth + x] = InverseLerp(MinNoiseHeight,MaxNoiseHeight,noiseMap[y * MapWidth + x]);
		}
	}
	return noiseMap;
}

float UNoiseHelpers::InverseLerp(float xx, float yy, float value)
{
	return (value - xx)/(yy - xx);
}

UTexture2D* UNoiseHelpers::GenerateHeightMap(TArray<float> HeightValues, int TextureWidth, FString Name)
{
	FString PackageName = TEXT("/Game/ProceduralTextural/");
	PackageName += Name;
	UPackage* Package = CreatePackage(NULL,*PackageName);
	Package->FullyLoad();
	
	UTexture2D* HeightMap = NewObject<UTexture2D>(Package, *Name, RF_Public | RF_Standalone | RF_MarkAsRootSet);

	HeightMap->AddToRoot();
	HeightMap->SetPlatformData(new FTexturePlatformData());
	auto PlatformData = HeightMap->GetPlatformData();
	PlatformData->SizeX = TextureWidth;
	PlatformData->SizeY = TextureWidth;
	PlatformData->SetNumSlices(1);
	PlatformData->PixelFormat = EPixelFormat::PF_B8G8R8A8;

	uint8* Pixels = new uint8[TextureWidth * TextureWidth * 4];
	for(int x = 0; x < TextureWidth; x++)
	{
		for(int y = 0; y < TextureWidth; y++)
		{
			int CurrentPixelIndex = ((y * TextureWidth) + x);
			Pixels[4 * CurrentPixelIndex] = 
			Pixels[4 * CurrentPixelIndex + 1] = 
			Pixels[4 * CurrentPixelIndex + 2] =  255 * HeightValues[CurrentPixelIndex];
			Pixels[4 * CurrentPixelIndex + 3] = 255;
		}
	}
	
	FTexture2DMipMap* Mip = new(HeightMap->PlatformData->Mips) FTexture2DMipMap();
	Mip->SizeX = TextureWidth;
	Mip->SizeY = TextureWidth;
	Mip->BulkData.Lock(LOCK_READ_WRITE);
	uint8* TextureData = (uint8*) Mip->BulkData.Realloc(TextureWidth * TextureWidth * 4);
	FMemory::Memcpy(TextureData, Pixels, sizeof(uint8) * TextureWidth * TextureWidth * 4);
	Mip->BulkData.Unlock();
	HeightMap->Source.Init(TextureWidth,TextureWidth,1,1,TSF_BGRA8,Pixels);
	HeightMap->UpdateResource();
	Package->MarkPackageDirty();
	FAssetRegistryModule::AssetCreated(HeightMap);
	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	bool bSaved = UPackage::SavePackage(Package, HeightMap, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr, true, true, SAVE_NoError);

	delete[] Pixels;
	return HeightMap;
}

