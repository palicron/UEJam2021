// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AInteractiveActor.h"
#include "KeyActor.generated.h"

/**
 * 
 */
UCLASS()
class UEJAM2021_API AKeyActor : public AAInteractiveActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyStats")
		float OpenRaidus = 250.f;
	// Sets default values for this actor's properties
	 AKeyActor();
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		 FTransform StarTransform;
	 UFUNCTION(BlueprintCallable)
		 void ResetKey();
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class USphereComponent* OpenSphere;

	UFUNCTION()
		void OpenDoor(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
	
	UFUNCTION(BlueprintCallable)
		void DisableAllPhyscis();
	
};
