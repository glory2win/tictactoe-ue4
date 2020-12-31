// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

	public:


	UFUNCTION(BlueprintCallable, Category = "Test")
	void TestFunction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void OnReplayButtonClicked();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void SetInfoText(FName Info);
	
};
