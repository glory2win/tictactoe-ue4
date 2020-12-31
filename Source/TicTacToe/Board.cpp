// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Block.h"
#include "GameHUD.h"
// #include "Editor/EditorEngine.h"

UBlockGrid::UBlockGrid() = default;

void UBlockGrid::Init(const uint32 SizeOfGrid)
{
	Size = SizeOfGrid;
	BlockArray.Empty(Size * Size);
}

ABlock* UBlockGrid::GetBlockAt(const uint32 Row, const uint32 Column) const
{
	 return BlockArray[Row * Size + Column];
}

void UBlockGrid::Add(ABlock* Block)
{
	BlockArray.Add(Block);
}

void UBlockGrid::ResetGrid() const
{
	for(const auto& Block : BlockArray)
	{
		Block->ResetBlock();
	}
}

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	CreateBoard();
}

void ABoard::CreateBoard()
{
	// make grid with blocks and assign the reference.
	if(!BlockPrefab) return;
	auto* World = GetWorld();
	if(!World) return;
	
	// GEngine->AddOnScreenDebugMessage(0,3.f,FColor::Cyan, FString("Size: " + FString::FromInt(Size)));

	UE_LOG(LogTemp, Warning, TEXT("Creating board..."));

	Grid = NewObject<UBlockGrid>();
	Grid->Init(this->Size); // Board's size is 3x3 usually.

	
	auto BlockIndex = 0;	
	
	for (int i=0; i < Size; i++)
	{
		// Block2DArray.Add(FBlock1DArray()); // Add a row array
		
		for(int j=0; j < Size; j++)
		{
			const float XOffSet = i * BlockSpacing;
			const float YOffSet = j * BlockSpacing;
			const FVector BlockLocation = FVector(XOffSet,YOffSet,0.0f) + GetActorLocation();

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;

			ABlock* NewBlock = GetWorld()->SpawnActor<ABlock>(
				BlockPrefab,
				BlockLocation,
				FRotator(90.0f,0.0f,0.0f),
				SpawnParameters);
			
			NewBlock->BoardRef = this;
			/*FString Rename = FString("Block_" + FString::FromInt(i) + "_" + FString::FromInt(j));
			FActorLabelUtilities::RenameExistingActor(NewBlock, Rename,true);*/
			NewBlock->AttachToActor(NewBlock->BoardRef, FAttachmentTransformRules::KeepWorldTransform);
			NewBlock->BlockIndex = ++BlockIndex; // starts from 1 to 9
			// Block2DArray[i].Add(NewBlock); // Add cell/block into the row

			Grid->Add(NewBlock);

			auto ID =   Grid->GetBlockAt(i,j)->BlockID;
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::FromInt(ID));

			// GEngine->AddOnScreenDebugMessage(20, 20.f, FColor::Yellow, FString(NewBlock->GetActorLocation().ToString()));

			UE_LOG(LogTemp, Warning, TEXT("Block loc: %s"), *NewBlock->GetActorLocation().ToString());	
			
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Board created"));

	// GEngine->AddOnScreenDebugMessage(10,3.f,FColor::Cyan, FString("Board created"));
}

void ABoard::SetPlayerTurn(const int32 CurrentPlayerId) const
{
	GameModeRef->CurrentPlayerId = CurrentPlayerId;
	
	if(CurrentPlayerId == ATicTacToeGameMode::Player1Id)
	{		
		GameModeRef->GameHUDRef->SetInfoText(FName(TEXT("Player 1 [X] Turn...")));
	}
	else if(CurrentPlayerId == ATicTacToeGameMode::Player2Id)
	{
		GameModeRef->GameHUDRef->SetInfoText(FName(TEXT("Player 2 [O] Turn...")));		
	}
}

void ABoard::ResetBoard()
{
	Grid->ResetGrid();	
	RemainEmptyCells = Size * Size;
}

void ABoard::CheckBoard()
{
	// TODO: Write game board check logic here and update the UI.

	const bool MatchFound = IsMatchFound();
	if(MatchFound && GameModeRef->CurrentPlayerId == ATicTacToeGameMode::Player1Id)
	{
		// Player 2 wins
		GameModeRef->ShowResult(1); // 0 - player 1 win, 1 - player 2 win, -1 is a draw.
		return;
	}
	
	if(MatchFound && GameModeRef->CurrentPlayerId == ATicTacToeGameMode::Player2Id)
	{
		GameModeRef->ShowResult(0);
		return;
	}

	if(!MatchFound && RemainEmptyCells <= 0)
	{
		GameModeRef->ShowResult(-1);
	}	

}

bool ABoard::IsMatchFound()
{
	
#pragma region 2D ARRAY SOLUTION // Need to test.
	// Line match check - Horizontal and Vertical
	/*for(int i = 0; i < Size; i++)
	{
		auto a = Block2DArray[0];
		auto b = a[0];
		
		if( (Block2DArray[i][0]->BlockID == Block2DArray[i][1]->BlockID &&
            Block2DArray[i][0]->BlockID == Block2DArray[i][2]->BlockID) ||
            (Block2DArray[0][i]->BlockID == Block2DArray[1][i]->BlockID &&
            Block2DArray[0][i]->BlockID == Block2DArray[2][i]->BlockID))
		{
			return true;	
		}			
			
	}

	// Diagonal match check

	if((Block2DArray[0][0]->BlockID == Block2DArray[1][1]->BlockID &&
		Block2DArray[0][0]->BlockID == Block2DArray[2][2]->BlockID) ||
		(Block2DArray[2][0]->BlockID == Block2DArray[1][1]->BlockID &&
		  Block2DArray[2][0] ->BlockID == Block2DArray[0][2]->BlockID))
	{
		return true;	
	}
	return false;*/
	
#pragma endregion
	
	for(int i = 0; i < Size; i++)
	{
		// Horizontal line check
		bool MatchFound = Grid->GetBlockAt(i, 0)->BlockID == Grid->GetBlockAt(i, 1)->BlockID &&
			Grid->GetBlockAt(i, 0)->BlockID == Grid->GetBlockAt(i, 2)->BlockID;
		if(MatchFound) return true;

		// Vertical line check
		MatchFound = Grid->GetBlockAt(0,i)->BlockID == Grid->GetBlockAt(1,i)->BlockID &&
						   Grid->GetBlockAt(0,i)->BlockID == Grid->GetBlockAt(2,i)->BlockID;
		if(MatchFound) return true;

		// Diagonals check
		MatchFound = Grid->GetBlockAt(0,0)->BlockID == Grid->GetBlockAt(1,1)->BlockID &&
					 Grid->GetBlockAt(0,0)->BlockID == Grid->GetBlockAt(2,2)->BlockID;
		if(MatchFound) return true;

		MatchFound = Grid->GetBlockAt(0,2)->BlockID == Grid->GetBlockAt(1,1)->BlockID &&
             Grid->GetBlockAt(0,2)->BlockID == Grid->GetBlockAt(2,0)->BlockID;
		if(MatchFound) return true;
	}

	return false;	
}



