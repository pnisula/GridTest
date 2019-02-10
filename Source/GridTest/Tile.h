// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

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
};

UCLASS()
class GRIDTEST_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
