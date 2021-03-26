// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ParkourGameGameMode.generated.h"

UCLASS(minimalapi)
class AParkourGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AParkourGameGameMode();

	virtual void BeginPlay();

	void AddFloor();

	TSubclassOf<AActor> NewFloor;

	TSubclassOf<UUserWidget> UMGUIMainAsset;

	UUserWidget* MainUI;

public:
	FTransform NextTransform;

};



