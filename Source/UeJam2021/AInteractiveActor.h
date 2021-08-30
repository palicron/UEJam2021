// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AInteractiveActor.generated.h"

UENUM(BlueprintType)
enum class EInter_Type: uint8
{
	EI_Grab  UMETA(DisplayName = "Grabe Objet"),
	EI_interactible UMETA(DisplayName = "Interactable Objet"),
	EI_PowerUp UMETA(DisplayName = "Power Up Object")
	
};

UCLASS()
class UEJAM2021_API AAInteractiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAInteractiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Objet Config")
		UStaticMeshComponent* MeshComponent;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Objet Config")
		EInter_Type Type = EInter_Type::EI_Grab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objet Config")
		bool bCanBeLaunch = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objet Config")
		class  UTexture2D* Icon;
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintCallable,Category="Interactive Object")
	virtual void OnGrab();
	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	virtual void OnRealesed();
	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	virtual void OnIntereact();
	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	virtual void OnLaunch();
	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	virtual void OnFell();
	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	virtual void OnHold();
	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	virtual void LaunchObjet(FVector Direction,float force);
	
	

};
