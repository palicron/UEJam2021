// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "Door_Actor.h"
#include "PowerBank.h"
#include "KeyActor.h"

#include "UeJam2021GameMode.h"
#include "Kismet/GameplayStatics.h"

AKeyActor::AKeyActor()
{
	PrimaryActorTick.bCanEverTick = false;


	OpenSphere = CreateDefaultSubobject<USphereComponent>(TEXT("KeyOpen"));
	OpenSphere->SetSphereRadius(OpenRaidus);
	OpenSphere->SetupAttachment(MeshComponent);

	OpenSphere->OnComponentBeginOverlap.AddDynamic(this, &AKeyActor::OpenDoor);
}

void AKeyActor::BeginPlay()
{
	Super::BeginPlay();
	StarTransform = GetActorTransform();
}

void AKeyActor::OpenDoor(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* OtherComp,
                         int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	APowerBank* power = Cast<APowerBank>(otherActor);
	if(power)
	{
		power->OpenConnections(this);
	}
}

void AKeyActor::DisableAllPhyscis()
{
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OpenSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetSimulatePhysics(false);
}

void AKeyActor::ResetKey()
{
	AGameModeBase* aa = UGameplayStatics::GetGameMode(GetWorld());
	auto MyMode = (AUeJam2021GameMode*)aa;
	if (MyMode)
	{
		if (MyMode->LevelDestroid)
		{
			Destroy();
		}
		else
		{
			SetActorTransform(StarTransform);
			GetRootComponent()->ComponentVelocity = FVector::ZeroVector;
		}
	}
}
