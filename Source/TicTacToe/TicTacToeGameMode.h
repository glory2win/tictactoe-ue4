// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TicTacToeGameMode.generated.h"


UENUM()
enum class EPlayerChoice
{
	Player_1,
    Player_2
};

UCLASS()
class TICTACTOE_API ATicTacToeGameMode : public AGameModeBase
{
	GENERATED_BODY()

	protected:

	virtual void BeginPlay() override;

	public:

	ATicTacToeGameMode();

	/** Properties */

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	EPlayerChoice PlayerTurn;

	static constexpr int32 Player1Id = 100;
	static constexpr int32 Player2Id = 200;
	int32 CurrentPlayerId;

	UPROPERTY(EditAnywhere, Category = "Board")
	TSubclassOf<class ABoard> BoardPrefab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	class UGameHUD* GameHUDRef;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "References")
	class ABoard* BoardRef;
	

	/** Functions */

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void AddGameHUD();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ReplayGame();

	UFUNCTION()
	void ShowResult(int Result);

	FORCEINLINE bool IsGameRunning() const { return bIsGameRunning;}

private:
	
	UPROPERTY()
	bool bIsGameRunning;
	
};


	