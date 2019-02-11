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
			TileInfo[i].isSelected = true;
			HideTopBorders(i, selectedTile);
			HideBottomBorders(i, selectedTile);
			HideLeftBorders(i, selectedTile);
			HideRightBorders(i, selectedTile);
		}
	}	
}
void ATileManager::HideTopBorders(int index, AActor* selectedTile)
{			
	if (TileInfo[index].row < 1) return;
	if (!TileInfo[index - RowsToSpawn].isSelected) return;
	
	CheckTileOnBottom(TileInfo[index - RowsToSpawn].Tile);

	ATile* tile = (ATile*)TileInfo[index].Tile;
	if (tile == nullptr) return;
		
	tile->HideTopBorder();								
}
void ATileManager::HideBottomBorders(int index, AActor* selectedTile)
{		
	if (TileInfo[index].row >= RowsToSpawn-1) return;	
	if (!TileInfo[index + RowsToSpawn].isSelected) return;

	CheckTileOnTop(TileInfo[index + RowsToSpawn].Tile);

	ATile* tile = (ATile*)TileInfo[index].Tile;
	if (tile == nullptr) return;
		
	tile->HideBottomBorder();						
}
void ATileManager::HideLeftBorders(int index, AActor* selectedTile)
{	
	if (TileInfo[index].column < 1) return;
	if (!TileInfo[index - 1].isSelected) return;
		
	CheckTileOnLeft(TileInfo[index - 1].Tile);

	ATile* tile = (ATile*)TileInfo[index].Tile;
	if (tile == nullptr) return;

	tile->HideRightBorder();
}
void ATileManager::HideRightBorders(int index, AActor* selectedTile)
{
	if (TileInfo[index].column >= ColumnsToSpawn - 1) return;	
	if (!TileInfo[index + 1].isSelected) return;
		
	CheckTileOnRight(TileInfo[index + 1].Tile);

	ATile* tile = (ATile*)TileInfo[index].Tile;
	if (tile == nullptr) return;
			
	tile->HideLeftBorder();
}
void ATileManager::CheckTileOnBottom(AActor* tileActor)
{	
	ATile* tile = (ATile*)tileActor;
	if (tile != nullptr)
	{
		tile->HideBottomBorder();		
	}			
}
void ATileManager::CheckTileOnRight(AActor* tileActor)
{
	ATile* tile = (ATile*)tileActor;
	if (tile != nullptr)
	{
		tile->HideRightBorder();
	}	
}
void ATileManager::CheckTileOnLeft(AActor* tileActor)
{
	ATile* tile = (ATile*)tileActor;
	if (tile != nullptr)
	{
		tile->HideLeftBorder();
	}	
}
void ATileManager::CheckTileOnTop(AActor* tileActor)
{
	ATile* tile = (ATile*)tileActor;
	if (tile != nullptr)
	{
		tile->HideTopBorder();
	}
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

