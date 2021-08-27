// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM()
enum class ETileType:uint8
{
	T_Single UMETA(DisplayName = "Single"),
	T_WhitLife UMETA(DisplayName = "Life tile"),
	T_moving UMETA(DisplayName = "moving tile"),
};
UCLASS()
class UEJAM2021_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* MeshComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "tile config")
		ETileType type = ETileType::T_Single;

	UFUNCTION(BlueprintCallable)
		void GravityEvent();

};
