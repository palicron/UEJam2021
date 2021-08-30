// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerBank.h"

// Sets default values
APowerBank::APowerBank()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

}

// Called when the game starts or when spawned
void APowerBank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerBank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

