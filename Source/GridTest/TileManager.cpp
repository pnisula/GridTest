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
void ATileManager::HideTopBorders(AActor* selectedTile)
{		
	for (int i = 0; i < TileInfo.Num(); i++)
	{				
		if (TileInfo[i].Tile == selectedTile)
		{
			TileInfo[i].isSelected = true;
			UE_LOG(LogTemp, Warning, TEXT("Current -> Row: %d, Column: %d"), TileInfo[i].row, TileInfo[i].column);

			if (TileInfo[i].row > 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Test"));
				bool wasSelected = CheckTileOnBottom(TileInfo[i].row - 1, TileInfo[i].column);
				if (wasSelected)
				{
					ATile* tile = (ATile*)TileInfo[i].Tile;
					if (tile != nullptr)
					{
						tile->HideTopBorder();
					}
				}
			}			
			return;
		}		
	}	
}
void ATileManager::HideBottomBorders(AActor* selectedTile)
{
	for (int i = 0; i < TileInfo.Num(); i++)
	{
		if (TileInfo[i].Tile == selectedTile)
		{
			TileInfo[i].isSelected = true;
			UE_LOG(LogTemp, Warning, TEXT("Current -> Row: %d, Column: %d"), TileInfo[i].row, TileInfo[i].column);

			if (TileInfo[i].row < RowsToSpawn-1)
			{
				UE_LOG(LogTemp, Warning, TEXT("Test"));
				bool wasSelected = CheckTileOnTop(TileInfo[i].row + 1, TileInfo[i].column);
				if (wasSelected)
				{
					ATile* tile = (ATile*)TileInfo[i].Tile;
					if (tile != nullptr)
					{
						tile->HideBottomBorder();
					}
				}
			}
			return;
		}
	}
}
void ATileManager::HideLeftBorders(AActor* selectedTile)
{
	for (int i = 0; i < TileInfo.Num(); i++)
	{
		if (TileInfo[i].Tile == selectedTile)
		{
			TileInfo[i].isSelected = true;			

			if (TileInfo[i].column > 0)
			{				
				bool wasSelected = CheckTileOnLeft(TileInfo[i].row, TileInfo[i].column-1);
				if (wasSelected)
				{
					ATile* tile = (ATile*)TileInfo[i].Tile;
					if (tile != nullptr)
					{
						tile->HideRightBorder();
					}
				}
			}
			return;
		}
	}
}
void ATileManager::HideRightBorders(AActor* selectedTile)
{
	for (int i = 0; i < TileInfo.Num(); i++)
	{
		if (TileInfo[i].Tile == selectedTile)
		{
			TileInfo[i].isSelected = true;			

			if (TileInfo[i].column < ColumnsToSpawn - 1)
			{				
				bool wasSelected = CheckTileOnRight(TileInfo[i].row , TileInfo[i].column+1);
				if (wasSelected)
				{
					ATile* tile = (ATile*)TileInfo[i].Tile;
					if (tile != nullptr)
					{
						tile->HideLeftBorder();
					}
				}
			}
			return;
		}
	}
}
bool ATileManager::CheckTileOnBottom(int row, int column)
{	
	for (int i = 0; i < TileInfo.Num(); i++)
	{
		if (TileInfo[i].row == row && TileInfo[i].column == column)
		{
			if (TileInfo[i].isSelected == true)
			{
				ATile* tile = (ATile*)TileInfo[i].Tile;
				if (tile != nullptr)
				{
					tile->HideBottomBorder();
					return true;
				}
			}
		}
	}
	return false;
}
bool ATileManager::CheckTileOnRight(int row, int column)
{
	for (int i = 0; i < TileInfo.Num(); i++)
	{
		if (TileInfo[i].row == row && TileInfo[i].column == column)
		{
			if (TileInfo[i].isSelected == true)
			{
				ATile* tile = (ATile*)TileInfo[i].Tile;
				if (tile != nullptr)
				{
					tile->HideRightBorder();
					return true;
				}
			}
		}
	}
	return false;
}
bool ATileManager::CheckTileOnLeft(int row, int column)
{
	for (int i = 0; i < TileInfo.Num(); i++)
	{
		if (TileInfo[i].row == row && TileInfo[i].column == column)
		{
			if (TileInfo[i].isSelected == true)
			{
				ATile* tile = (ATile*)TileInfo[i].Tile;
				if (tile != nullptr)
				{
					tile->HideLeftBorder();
					return true;
				}
			}
		}
	}
	return false;
}
bool ATileManager::CheckTileOnTop(int row, int column)
{
	for (int i = 0; i < TileInfo.Num(); i++)
	{
		if (TileInfo[i].row == row && TileInfo[i].column == column)
		{
			if (TileInfo[i].isSelected == true)
			{
				ATile* tile = (ATile*)TileInfo[i].Tile;
				if (tile != nullptr)
				{
					tile->HideTopBorder();
					return true;
				}
			}
		}
	}
	return false;
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

