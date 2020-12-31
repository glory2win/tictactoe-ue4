// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacToeGameMode.h"
#include "Board.h"
#include "GameHUD.h"

ATicTacToeGameMode::ATicTacToeGameMode()
{
	
}


void ATicTacToeGameMode::BeginPlay()
{
	if(BoardPrefab)
	{
		auto* World = GetWorld();
		if(World)
		{
			FActorSpawnParameters Parameters;
			Parameters.Owner =this;
			
			BoardRef = World->SpawnActor<ABoard>(BoardPrefab, FVector(-130.f,-130.f,0.f), FRotator::ZeroRotator,Parameters);
			if(BoardRef)
			{
				BoardRef->GameModeRef = this;				
				UE_LOG(LogTemp, Warning, TEXT("Board instance has been created!"));
			}
		}
	}

	AddGameHUD();

	ReplayGame();
}

void ATicTacToeGameMode::ReplayGame()
{
	BoardRef->ResetBoard();
	CurrentPlayerId = Player1Id;
	GameHUDRef->SetInfoText(FName(TEXT("Player 1 [X] Turn...")));
	bIsGameRunning = true;
	UE_LOG(LogTemp, Warning, TEXT("Game is reset"));
}

void ATicTacToeGameMode::ShowResult(int Result)
{
	switch (Result)
	{
		case 0:
			GameHUDRef->SetInfoText(FName(TEXT("Player 1 [X] won the match!")));
			break;
		case 1:
			GameHUDRef->SetInfoText(FName(TEXT("Player 2 [O] won the match!")));
			break;
		case -1:
			GameHUDRef->SetInfoText(FName(TEXT("The match ended with a draw!")));
			break;
		default: ;
	}
	bIsGameRunning = false;
}