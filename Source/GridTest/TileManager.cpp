// Fill out your copyright notice in the Description page of Project Settings.

#include "TileManager.h"


// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileManager::SpawnTiles()
{		
	int firstTilePositionX = -(RowsToSpawn / 2.0f) * TileWidth + (TileWidth / 2.0f);
	int firstTilePositionY = -(ColumnsToSpawn / 2.0f) * TileHeight + (TileHeight / 2.0f);

	for (int i = 0; i < RowsToSpawn; i++)
	{
		for (int j = 0; j < ColumnsToSpawn; j++)
		{
			AActor* Spawned = GetWorld()->SpawnActor<AActor>(TileToSpawn);
			if (Spawned == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Tile To Spawn wasn't set correctly"));
				return;
			}
			
			int tilePositionX = firstTilePositionX + i * TileWidth;
			int tilePositionY = firstTilePositionY + j * TileHeight;

			FVector SpawnPosition = FVector(tilePositionX, tilePositionY, 0);
			Spawned->SetActorRelativeLocation(SpawnPosition);
			Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		}
	}

}

