// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class PARKOURGAME_API ACoin : public AActor
{
	GENERATED_BODY()

		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Re_CoinMesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CoinMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Re_BoxComponent", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CoinBox;


public:	
	// Sets default values for this actor's properties
	ACoin();
 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void Print_F(FString MessageString);

	UFUNCTION()
	void WhenCoinHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
