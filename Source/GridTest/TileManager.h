// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileManager.generated.h"

USTRUCT()
struct FTileInfo
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* Tile;

	UPROPERTY()
	int row;

	UPROPERTY()
	int column;

	UPROPERTY()
	bool isSelected = false;

	AActor* GetTile()
	{
		return Tile;
	}
	//Check
	bool ActorIsValid() const
	{
		if (!Tile) return false;
		return Tile->IsValidLowLevel();
	}

	//Constructor
	FTileInfo()
	{
		//Always initialize your USTRUCT variables!
		//   exception is if you know the variable type has its own default constructor
		row = NULL;
		column = NULL;
		Tile = NULL;
	}
	FTileInfo(AActor* tile, int row, int column)
	{
		this->Tile = tile;
		this->row = row;
		this->column = column;
	}
};

UCLASS()
class GRIDTEST_API ATileManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> TileToSpawn;

	UPROPERTY(EditDefaultsOnly)
	int RowsToSpawn;

	UPROPERTY(EditDefaultsOnly)
	int ColumnsToSpawn;
	
	UPROPERTY(EditDefaultsOnly)
	int TileWidth;

	UPROPERTY(EditDefaultsOnly)
	int TileHeight;

	UPROPERTY()
	TArray<FTileInfo> TileInfo;

	UFUNCTION(BlueprintCallable)
	void SpawnTiles();	

	UFUNCTION(BlueprintCallable)
	void HideTopBorders(AActor* selectedTile);
	UFUNCTION(BlueprintCallable)
	void HideBottomBorders(AActor* selectedTile);
	UFUNCTION(BlueprintCallable)
	void HideLeftBorders(AActor* selectedTile);
	UFUNCTION(BlueprintCallable)
	void HideRightBorders(AActor* selectedTile);

	UFUNCTION()
	bool CheckTileOnLeft(int row, int column);
	UFUNCTION()
	bool CheckTileOnRight(int row, int column);
	UFUNCTION()
	bool CheckTileOnTop(int row, int column);
	UFUNCTION()
	bool CheckTileOnBottom(int row, int column);
	
	UFUNCTION(BlueprintCallable)
	AActor* GetTileByRowAndColumn(int row, int column);		
};
