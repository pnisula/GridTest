// Fill out your copyright notice in the Description page of Project Settings.

#include "TileManager.h"
#include "Tile.h"

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

			//Populate list
			FTileInfo newTile = FTileInfo(Spawned, i, j);
			TileInfo.Add(newTile);
		}
	}
}
void ATileManager::HideBorders(AActor* selectedTile)
{	
	for (int i = 0; i < TileInfo.Num(); i++)
	{
		if (TileInfo[i].Tile == selectedTile)
		{
			ATile* tile = Cast<ATile>(selectedTile);
			tile->isSelected = true;

			UE_LOG(LogTemp, Warning, TEXT("Tile found in tileInfo: %s"), *selectedTile->GetName());
			UE_LOG(LogTemp, Warning, TEXT("Tilerow: %d"), TileInfo[i].row);

			if (TileInfo[i].row > 0)
			{
				CheckTileOnLeft(TileInfo[i].row, TileInfo[i].column);
			}
			if (TileInfo[i].row < TileInfo.Num() - 1)
			{
				CheckTileOnRight(TileInfo[i].row, TileInfo[i].column);
			}
			if (TileInfo[i].column > 0)
			{
				CheckTileOnBottom(TileInfo[i].row, TileInfo[i].column);
				
			}
			if(TileInfo[i].column < TileInfo.Num() - 1)
			{
				CheckTileOnTop(TileInfo[i].row, TileInfo[i].column);
			}
		}
	}
}
void ATileManager::CheckTileOnLeft(int row, int column)
{
	AActor* TileOnLeft = GetTileByRowAndColumn(row - 1, column);
	ATile* tile = Cast<ATile>(TileOnLeft);
	if (tile->isSelected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tile was selected"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tile was not selected"));
	}
	
}
void ATileManager::CheckTileOnRight(int row, int column)
{

}
void ATileManager::CheckTileOnTop(int row, int column)
{

}
void ATileManager::CheckTileOnBottom(int row, int column)
{

}

AActor* ATileManager::GetTileByRowAndColumn(int row, int column)
{
	for (int i = 0; i < TileInfo.Num(); i++)
	{
		if (TileInfo[i].row == row && TileInfo[i].column == column)
		{
			return TileInfo[i].Tile;
		}
	}
	return nullptr;
}

