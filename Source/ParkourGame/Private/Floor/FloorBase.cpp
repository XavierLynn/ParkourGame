// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor/FloorBase.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "../ParkourGameCharacter.h"
#include "../ParkourGameGameMode.h"

// Sets default values
AFloorBase::AFloorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SenceComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BP_RootComponent"));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BP_BaseMesh"));

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BP_BoxComponent"));

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("BP_SpawnPoint"));

	SpawnPointR = CreateDefaultSubobject<UArrowComponent>(TEXT("BP_SpawnPointR"));

	SpawnPointL = CreateDefaultSubobject<UArrowComponent>(TEXT("BP_SpawnPointL"));

	BaseMesh->SetupAttachment(SenceComponent);
	BoxComponent->SetupAttachment(SenceComponent);
	SpawnPoint->SetupAttachment(SenceComponent);
	SpawnPointR->SetupAttachment(SenceComponent);
	SpawnPointL->SetupAttachment(SenceComponent);

	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AFloorBase::OnBoxOverlap);


}

// Called when the game starts or when spawned
void AFloorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FTransform AFloorBase::GetAttachToTransform(FVector MyLocation)
{
	FTransform Transform;
	Transform.SetLocation(SpawnPoint->GetComponentLocation());
	Transform.SetRotation(SpawnPoint->GetComponentQuat());
	return Transform;
}

void AFloorBase::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Print_F("IsOverlap");
	if (OtherActor->IsA(AParkourGameCharacter::StaticClass()))
	{
		if (GetWorld())
		{
			AParkourGameGameMode* CurGameMode = Cast<AParkourGameGameMode>(GetWorld()->GetAuthGameMode());
			if (CurGameMode)
			{
				CurGameMode->AddFloor();


				if (MyTimerHandle.IsValid())
				{
					GetWorldTimerManager().ClearTimer(MyTimerHandle);
				}
				GetWorldTimerManager().SetTimer(MyTimerHandle, this, &AFloorBase::DestroyThis, 1.0f, true);
			}
		
		}
	}
}



void AFloorBase::Print_F(FString PrintString)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Blue, PrintString);
	}
}

void AFloorBase::DestroyThis()
{
	Print_F("IsDestroy");
	Destroy();
}

