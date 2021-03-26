// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG_Main.generated.h"

/**
 * 
 */
UCLASS()
class PARKOURGAME_API UUMG_Main : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = UI)
	FText CoinNum;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = UI)
	FText CharacterDistance;
};
