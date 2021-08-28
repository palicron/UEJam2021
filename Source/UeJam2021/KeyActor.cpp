// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "Door_Actor.h"
#include "KeyActor.h"

AKeyActor::AKeyActor()
{
	PrimaryActorTick.bCanEverTick = false;


	OpenSphere = CreateDefaultSubobject<USphereComponent>(TEXT("KeyOpen"));
	OpenSphere->SetSphereRadius(OpenRaidus);
	OpenSphere->SetupAttachment(MeshComponent);

	OpenSphere->OnComponentBeginOverlap.AddDynamic(this, &AKeyActor::OpenDoor);
}

void AKeyActor::OpenDoor(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* OtherComp,
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	ADoor_Actor* door = Cast<ADoor_Actor>(otherActor);
	if(door)
	{
		door->OpenDoor(this);
	}
}

void AKeyActor::DisableAllPhyscis()
{
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetSimulatePhysics(false);
}
