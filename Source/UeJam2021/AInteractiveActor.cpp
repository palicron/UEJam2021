// Fill out your copyright notice in the Description page of Project Settings.


#include "AInteractiveActor.h"

// Sets default values
AAInteractiveActor::AAInteractiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionProfileName(TEXT("InteracitveObjet"));

}

// Called when the game starts or when spawned
void AAInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAInteractiveActor::OnGrab()
{
}

void AAInteractiveActor::OnRealesed()
{
}

void AAInteractiveActor::OnIntereact()
{
}

void AAInteractiveActor::OnLaunch()
{
}

void AAInteractiveActor::OnFell()
{
}

void AAInteractiveActor::OnHold()
{
}

void AAInteractiveActor::LaunchObjet(FVector Direction, float force)
{
	if(MeshComponent)
	{
		MeshComponent->AddImpulse(Direction * force, NAME_None, true);
	}
	
}



