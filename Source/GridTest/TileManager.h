// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "TileManager.generated.h"

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

	UFUNCTION(BlueprintCallable)
	void SpawnTiles();

	TArray<FTileInfo> TileInfo;
};
