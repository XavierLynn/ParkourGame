// Copyright Epic Games, Inc. All Rights Reserved.

#include "ParkourGameGameMode.h"
#include "ParkourGameCharacter.h"
#include "Floor/FloorBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "UMG/UMG_Main.h"

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

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Main(TEXT("/Game/UMG/WBP_UIMain"));


	UMGUIMainAsset = UI_Main.Class;

}

void AParkourGameGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		for (int32 i = 0;i<2;i++)
		{
			AddFloor();
		}
	}
	if (UMGUIMainAsset)
	{
		if (GetWorld())
		{
			MainUI = CreateWidget<UUserWidget>(GetWorld(), UMGUIMainAsset);
			if (MainUI)
			{
				MainUI->AddToViewport();
				UUMG_Main* MyMainUI = Cast<UUMG_Main>(MainUI);
				if (MyMainUI)
				{
					MyMainUI->CoinNum = FText::FromString(TEXT("0"));
					MyMainUI->CharacterDistance = FText::FromString(TEXT("0"));

				}
			
			}
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
