// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ParkourGameGameState.generated.h"

/**
 * 
 */
UCLASS()
class PARKOURGAME_API AParkourGameGameState : public AGameStateBase
{
	GENERATED_BODY()

	
public:

	AParkourGameGameState();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "G_CoinNum")
		int32 Glod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "G_Distance")
		int32 Distance;

};
