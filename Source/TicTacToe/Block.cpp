// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "Board.h"
#include "Editor/EditorEngine.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DummyRoot"));
	RootComponent = DummyRoot;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>("BlockModel");
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &ABlock::BlockClicked);   

	bIsAvailable = true;

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	if(!bIsAvailable || !BoardRef->GameModeRef->IsGameRunning()) return;

	if(BoardRef->GetPlayerTurnId() == ATicTacToeGameMode::Player1Id)
	{	
		BlockID = ATicTacToeGameMode::Player1Id;
		BlockMesh->SetMaterial(0, CrossBlockMaterial);
		BoardRef->SetPlayerTurn(ATicTacToeGameMode::Player2Id);
	}
	else if(BoardRef->GetPlayerTurnId() == ATicTacToeGameMode::Player2Id)
	{
		BlockID = ATicTacToeGameMode::Player2Id;
		BlockMesh->SetMaterial(0, RoundBlockMaterial);
		BoardRef->SetPlayerTurn(ATicTacToeGameMode::Player1Id);
	}

	bIsAvailable = false;
	BoardRef->RemainEmptyCells--;
	if(BoardRef->RemainEmptyCells < 0)
	{
		BoardRef->RemainEmptyCells = 0;
	}

	BoardRef->CheckBoard();

	UE_LOG(LogTemp, Warning, TEXT("Block clicked"));
}

void ABlock::ResetBlock()
{
	bIsAvailable = true;
	BlockID = BlockIndex;
	SetEmptyMaterial();
}

void ABlock::SetEmptyMaterial() const
{
	BlockMesh->SetMaterial(0, EmptyBlockMaterial);	
}

void ABlock::SetCrossMaterial() const
{
	BlockMesh->SetMaterial(0, CrossBlockMaterial);
}

void ABlock::SetRoundMaterial() const
{
	BlockMesh->SetMaterial(0, RoundBlockMaterial);
}




