// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TicTacToeGameMode.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class TICTACTOE_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	/** Properties*/
	
	bool bIsAvailable; /** Check block clickable */

	UPROPERTY(EditAnywhere, Category = "References")
	class ABoard* BoardRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials")
	UMaterial* EmptyBlockMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials")
	UMaterialInstance* CrossBlockMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials")
	UMaterialInstance* RoundBlockMaterial;

	UPROPERTY()
	uint32 BlockID;

	UPROPERTY()
	uint32 BlockIndex; // Index of the block on the grid.


	/** Functions */
	
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	UFUNCTION()
	void ResetBlock();

	UFUNCTION()
	void SetEmptyMaterial() const;

	UFUNCTION()
	void SetCrossMaterial() const;

	UFUNCTION()
	void SetRoundMaterial() const;
	

private:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "Block", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BlockMesh;	


};
