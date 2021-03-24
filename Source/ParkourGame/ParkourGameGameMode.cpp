// Copyright Epic Games, Inc. All Rights Reserved.

#include "ParkourGameGameMode.h"
#include "ParkourGameCharacter.h"
#include "Floor/FloorBase.h"
#include "UObject/ConstructorHelpers.h"

AParkourGameGameMode::AParkourGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	//NewFloor = LoadClass<AActor>(NULL,"CurFloor",TEXT(""));
	NewFloor = LoadClass<AActor>(NULL, TEXT("Blueprint'/Game/Floor/Blueprint/Floor.Floor_C'"));
}

void AParkourGameGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		for (int32 i = 0;i<9;i++)
		{
			AddFloor();
		}
	}
}

void AParkourGameGameMode::AddFloor()
{
	if (NewFloor!=nullptr)
	{
		const FVector MyLocation = NextTransform.GetLocation();
		const FRotator MyRototion(NextTransform.GetRotation());
		AFloorBase *MyFloor = GetWorld()->SpawnActor<AFloorBase>(NewFloor,MyLocation, MyRototion);
		NextTransform = MyFloor->GetAttachToTransform(MyLocation);
	}
}
