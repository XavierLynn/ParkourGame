// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorBase.generated.h"

UCLASS()
class PARKOURGAME_API AFloorBase : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sence", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SenceComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sence", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sence", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sence", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* SpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sence", meta = (AllowPrivateAccess = "true"))
		UArrowComponent* SpawnPointR;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sence", meta = (AllowPrivateAccess = "true"))
		UArrowComponent* SpawnPointL;


public:
	// Sets default values for this actor's properties
	AFloorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTransform GetAttachToTransform(FVector MyLocation);

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Print_F(FString PrintString);

	FTimerHandle MyTimerHandle;

	void DestroyThis();

};
