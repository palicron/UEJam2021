// Fill out your copyright notice in the Description page of Project Settings.


#include "AInteractiveActor.h"

// Sets default values
AAInteractiveActor::AAInteractiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionProfileName(TEXT("InteracitveObjet"));
	RootComponent = MeshComponent;

}

// Called when the game starts or when spawned
void AAInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAInteractiveActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FHitResult hit;
	FVector Star = GetActorLocation();
	FVector End = Star + (-GetActorUpVector() * 52.f);

	FCollisionQueryParams CollParams;
	CollParams.AddIgnoredActor(this);

	bool isGrounded = GetWorld()->LineTraceSingleByChannel(hit, Star, End, ECC_Visibility, CollParams);

	if(isGrounded)
	{
		//MeshComponent->SetLinearDamping(1.5f);
	
	}
	else
	{
		//MeshComponent->SetLinearDamping(0.01f);
		MeshComponent->AddForce(-GetActorUpVector().GetSafeNormal()*200.f);
	
	}
}

void AAInteractiveActor::OnGrab()
{
	//MeshComponent->GetBodyInstance()->bLockXTranslation = false;
	//MeshComponent->GetBodyInstance()->bLockYTranslation = false;
	//MeshComponent->GetBodyInstance()->bLockZTranslation = false;
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



