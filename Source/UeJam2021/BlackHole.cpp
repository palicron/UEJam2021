// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UeJam2021Character.h"
#include "BlackHole.h"

#include "Tile.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	InnerShpereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerShepreComp"));
	InnerShpereComp->SetSphereRadius(DeathZone);
	InnerShpereComp->SetupAttachment(MeshComp);

	InnerShpereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);

	LimitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("LimitOFforceSphere"));
	LimitSphere->SetSphereRadius(pullRadius);
	LimitSphere->SetupAttachment(MeshComp);

	DestroyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxLimits"));
	DestroyBox->SetBoxExtent(FVector(1.f));
	DestroyBox->SetupAttachment(MeshComp);
	DestroyBox->SetRelativeLocation(FVector(BoxInitStend.X/2, BoxInitStend.Y/2, BoxInitStend.Z/2));
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	DestroyBox->SetBoxExtent(BoxInitStend);
	GetWorldTimerManager().SetTimer(FlootDentroiTimer, this, &ABlackHole::DestroiTiles, DestroiIntervasle);
	
}

void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* otherActor,
	UPrimitiveComponent* OtherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if(otherActor)
	{
		otherActor->Destroy();
	}
}

void ABlackHole::PullDynamicObjets()
{
	TArray<UPrimitiveComponent*> OverlapComps;
	LimitSphere->GetOverlappingComponents(OverlapComps);

	for(int32 i=0;i<OverlapComps.Num();i++)
	{
	
		UPrimitiveComponent* primcomp = OverlapComps[i];
		if(primcomp && primcomp->IsSimulatingPhysics())
		{

			FVector ForceDir = (  GetActorLocation()- primcomp->GetOwner()->GetActorLocation());
			ForceDir.Z = 0;
			
			if(ForceDir.Size()<= eventHorizon)
			{
				
			
				primcomp->AddForce(ForceDir.GetSafeNormal() * Force * EventMultiply);
			}
			else
			{
				
				
				primcomp->AddForce(ForceDir.GetSafeNormal() * Force);
			}
		
		}
		else
		{
			AUeJam2021Character* pj = Cast<AUeJam2021Character>(primcomp->GetOwner());
			if(pj)
			{
				FVector ForceDir = (GetActorLocation() - primcomp->GetOwner()->GetActorLocation());
				ForceDir.Z = 0;
			
				if (ForceDir.Size() <= eventHorizon)
				{

					pj->GetCharacterMovement()->AddImpulse(ForceDir.GetSafeNormal() * (Forceplayer *EventMultiply));
				
				}
				else
				{
					

					//pj->GetCharacterMovement()->AddForce(ForceDir.GetSafeNormal() * Forceplayer);
					pj->GetCharacterMovement()->AddImpulse(ForceDir.GetSafeNormal() * Forceplayer);
				}
				
				
			}
		}
	}
	
	//LimitSphere
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PullDynamicObjets();
}

inline void ABlackHole::DestroiTiles()
{
	TArray<AActor*> tilesActors;
	DestroyBox->GetOverlappingActors(tilesActors);
	UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
	for (int32 i = 0;i < tilesActors.Num();i++)
	{
		ATile* CurrenTile = Cast<ATile>(tilesActors[i]);
		if(CurrenTile)
		{
			CurrenTile->GravityEvent();
		}
	}

	if(interationIndex< Iterations)
	{
		interationIndex++;
		GetWorldTimerManager().ClearTimer(FlootDentroiTimer);
		DestroiIntervasle *= intervalesVariance;
		BoxInitStend += BoxIncresePerIteration;
		DestroyBox->SetBoxExtent(BoxInitStend );
		GetWorldTimerManager().SetTimer(FlootDentroiTimer, this, &ABlackHole::DestroiTiles, DestroiIntervasle);
	
	}
	else
	{
		GetWorldTimerManager().ClearTimer(FlootDentroiTimer);
	}
	
	
}