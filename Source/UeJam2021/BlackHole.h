// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

UCLASS()
class UEJAM2021_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHole();

	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* MeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class USphereComponent* InnerShpereComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class USphereComponent* LimitSphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* DestroyBox;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
	UFUNCTION(BlueprintCallable)
		void PullDynamicObjets();

	int interationIndex = 0;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bh_Porpertes")
		float pullRadius = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bh_Porpertes")
		float eventHorizon = 350.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bh_Porpertes")
		float DeathZone = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bh_Porpertes")
		float Force = 125000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bh_Porpertes")
		float Forceplayer = 2500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bh_Porpertes")
		float EventMultiply = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bh_Porpertes")
		FVector BoxInitStend = FVector(400.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bh_Porpertes")
		float DestroiIntervasle = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bh_Porpertes")
		uint8 Iterations = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bh_Porpertes")
		FVector BoxIncresePerIteration = FVector(200.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bh_Porpertes")
		float intervalesVariance = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bh_Porpertes")
		float AirForceDivide = 6.f;
	FTimerHandle FlootDentroiTimer;


	UFUNCTION(BlueprintCallable)
		void DestroiTiles();

	
	

};


