// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Block.h"
#include "Core.h"
#include "GameFramework/Actor.h"
#include "TicTacToeGameMode.h"
#include "Board.generated.h"

USTRUCT()
struct FBlock1DArray // For 2D Array solution.

{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray< ABlock*> InnerArray;

	ABlock* operator[] (const int32 BlockIndex)
	{
		return InnerArray[BlockIndex];
	}

	const ABlock* operator[] (const int32 BlockIndex) const
	{
		return InnerArray[BlockIndex];
	}

	void Add(ABlock* Block)
	{
		InnerArray.Add(Block);
	}
};

UCLASS()
class UBlockGrid final : public UObject
{
	GENERATED_BODY()

public:
	UBlockGrid();	

	UFUNCTION()
	void Init(const uint32 SizeOfGrid);
	
	UFUNCTION()
	ABlock* GetBlockAt(const uint32 Row, const uint32 Column) const;

	UFUNCTION()
	void Add(ABlock* Block);

	UFUNCTION()
	void ResetGrid() const;
	

private:
	UPROPERTY()
	TArray<ABlock*> BlockArray;
	
	UPROPERTY()
	uint32 Size;
	
};

UCLASS()
class TICTACTOE_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Properties
	
	UPROPERTY(VisibleDefaultsOnly, Category = "References")
	ATicTacToeGameMode* GameModeRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
	TSubclassOf<class ABlock> BlockPrefab; // Pick the BP_Block from BP, that will be instantiated in the level at runtime.	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid") // Edit size in BP
	int32 Size;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid") // Edit spacing in BP
	float BlockSpacing;

	UPROPERTY()
	int RemainEmptyCells; 

	// Functions
	
	UFUNCTION()
    FORCEINLINE int32 GetPlayerTurnId() const { return GameModeRef->CurrentPlayerId; }

	UFUNCTION()
	void SetPlayerTurn(const int32 CurrentPlayerId) const;

	UFUNCTION()
    void ResetBoard();

	UFUNCTION()
	void CheckBoard();

	UFUNCTION()
	bool IsMatchFound();

private:

	/*UPROPERTY()
	TArray<FBlock1DArray> Block2DArray;*/

	UPROPERTY()
	UBlockGrid* Grid;
	 
	UFUNCTION()	
    void CreateBoard();
	
};
