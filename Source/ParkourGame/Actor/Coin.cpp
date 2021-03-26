// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "ParkourGameGameState.h"
#include "../ParkourGameGameMode.h"
#include "../ParkourGameCharacter.h"
#include "../UMG/UMG_Main.h"
#include "Components/BoxComponent.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("M_CoinMesh"));

	CoinBox = CreateDefaultSubobject<UBoxComponent>(TEXT("M_CoinBox"));

	RootComponent = CoinBox;

	CoinMesh->SetupAttachment(CoinBox);

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	CoinBox->OnComponentHit.AddDynamic(this, &ACoin::WhenCoinHit);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoin::Print_F(FString MessageString)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, MessageString);
	}
}

void ACoin::WhenCoinHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherActor->IsA(AParkourGameCharacter::StaticClass()))
	{

		if (GetWorld())
		{
		
		AParkourGameGameMode* MyGameMode = Cast<AParkourGameGameMode>(GetWorld()->GetAuthGameMode());
		AParkourGameGameState* MyGameState = Cast<AParkourGameGameState>(GetWorld()->GetGameState());

		if (MyGameMode && MyGameState)
		{
			MyGameState->Glod++;
			UUMG_Main* MyUMG = Cast<UUMG_Main>(MyGameMode->MainUI);
			if (MyUMG)
			{
				MyUMG->CoinNum = FText::FromString(FString::FromInt(MyGameState->Glod));
			}
		}
		}
		Destroy(true);
		Print_F("The Coin be Hit");
	
	}

}

