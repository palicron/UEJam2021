// Copyright Epic Games, Inc. All Rights Reserved.

#include "UeJam2021Character.h"
#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AInteractiveActor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


//////////////////////////////////////////////////////////////////////////
// AUeJam2021Character

AUeJam2021Character::AUeJam2021Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;


	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AUeJam2021Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AUeJam2021Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AUeJam2021Character::StopJumping);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AUeJam2021Character::MakeDash);
	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &AUeJam2021Character::TryToInteract);
	PlayerInputComponent->BindAction("launch", IE_Pressed, this, &AUeJam2021Character::LaunchGrabItem);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AUeJam2021Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUeJam2021Character::MoveRight);

	
}

void AUeJam2021Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CheckGround();
	AddPushDownForce();
	CheckMaxPressJump(DeltaSeconds);
	if (!bIsCarryingSomething)
		CheckForObjets();
	else
	{
		FVector grab = GetActorForwardVector();
		grab *= 100.f;
		grab.Z = 150.f;
		
		PhysicsHandle->SetTargetLocation(GetActorLocation() + (grab));
	
		if(FVector::Dist(GetActorLocation(), GrabObject->GetActorLocation())>=500.f)
		{
			RealseObjetc();
		}
	}
		

}

void AUeJam2021Character::MakeDash()
{
	//TODO Force depending of velocity
	if (canDash && isGrounded)
	{
		FVector direction = GetActorForwardVector();
		direction.Z = 0;

	
		LaunchCharacter(direction.GetSafeNormal() * 1000.f, false, false);
	
		
		canDash = false;
		GetWorldTimerManager().SetTimer(DashTime, this, &AUeJam2021Character::ResetDash, DashCd);
	}


}

void AUeJam2021Character::ResetDash()
{
	canDash = true;


}

void AUeJam2021Character::CheckGround()
{
	FHitResult hit;
	FVector Star = GetActorLocation();
	FVector End = Star + (-GetActorUpVector() * 100.f);

	FCollisionQueryParams CollParams;

	isGrounded = GetWorld()->LineTraceSingleByChannel(hit, Star, End, ECC_Visibility, CollParams);

	//DrawDebugLine(GetWorld(),Star,End,FColor::Red,false,1,0,1);


}

void AUeJam2021Character::Jump()
{
	Super::Jump();
	bIsJumping = true;
}

void AUeJam2021Character::StopJumping()
{
	Super::StopJumping();
	bIsJumping = false;
	JumpHoldTime = 0;
}



void AUeJam2021Character::AddPushDownForce()
{
	if (!isGrounded && !bIsJumping)
	{
		GetCharacterMovement()->AddForce(GetActorUpVector() * -350000.f);
	}



}

void AUeJam2021Character::CheckMaxPressJump(float DeltaTime)
{
	if (bIsJumping)
	{
		JumpHoldTime += DeltaTime;


		if (JumpHoldTime >= GetJumpMaxHoldTime())
		{
			bIsJumping = false;
		}
	}
}

void AUeJam2021Character::CheckForObjets()
{
	if (isGrounded)
	{
		 FVector start = GetActorLocation() + (GetActorForwardVector().GetSafeNormal()*50.f);
		start.Z -= 40.f;
		 FVector end = GetActorLocation() + (GetActorForwardVector().GetSafeNormal() * 50.f);
		 end.Z -= 40.f;
		TArray<AActor*> ActorTOIgnore;
		ActorTOIgnore.Add(GetOwner());

		FHitResult hitResult;

		const bool hitObject = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), start, end, 30.f, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), false, ActorTOIgnore,
			EDrawDebugTrace::None,hitResult,true);

		if(hitObject)
		{
			FHitResult hit;

			FVector Star = hitResult.GetActor()->GetActorLocation();
			FVector End = Star + (GetActorUpVector() * 100.f);

			FCollisionQueryParams CollParams;
			CollParams.AddIgnoredActor(hitResult.GetActor());

			if( !GetWorld()->LineTraceSingleByChannel(hit, Star, End, ECC_Visibility, CollParams))
			{
				TouchObjetct = Cast<AAInteractiveActor>(hitResult.GetActor());
				OnInteractOnrange(TouchObjetct);
			}
			else
			{
				TouchObjetct = nullptr;
			}
	
			
			
		}
		else
		{
			TouchObjetct = nullptr;
		}
	}
}

void AUeJam2021Character::TryToInteract()
{
	if(GrabObject && bIsCarryingSomething)
	{
		FHitResult hitH;
		FCollisionQueryParams CollParams;
		FVector Star = GetActorLocation() + (GetActorForwardVector() * 150.f);
		Star.Z += 200.f;
		bool forntHit = GetWorld()->LineTraceSingleByChannel(hitH, GetActorLocation(), Star, ECC_Visibility, CollParams);
		if(forntHit)
		{
			float distance = (GetActorLocation() - hitH.ImpactPoint).Size();
			Star = GetActorLocation() + (GetActorForwardVector() *(distance-20.f) );
		}
		FHitResult hit;
		FVector End = Star + (-GetActorUpVector() * 350.f);	
		CollParams.AddIgnoredActor(GrabObject);
		if( GetWorld()->LineTraceSingleByChannel(hit, Star, End, ECC_Visibility, CollParams))
		{
			
				FVector place = hit.GetActor()->GetActorLocation();
				place.Z = hit.ImpactPoint.Z +35.f;
				PhysicsHandle->ReleaseComponent();
				GrabObject->SetActorLocation(place);
			
		
		}
	
			RealseObjetc();
		

		
	}
	else
	{
	
		if(TouchObjetct)
		{
		
			UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(TouchObjetct->GetComponentByClass(UPrimitiveComponent::StaticClass()));
			if(primitive)
			{
				GrabObject = TouchObjetct;
				GrabObject->OnGrab();
				PhysicsHandle->GrabComponentAtLocation(primitive, NAME_None, TouchObjetct->GetActorLocation());
				
				bIsCarryingSomething = true;
				TouchObjetct = nullptr;
			}
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No hay objeto"));
		}
	}
}

void AUeJam2021Character::LaunchGrabItem()
{
	if (GrabObject && bIsCarryingSomething)
	{
		if(GrabObject->bCanBeLaunch)
		{
			UE_LOG(LogTemp, Warning, TEXT("Lanzando"));
			PhysicsHandle->ReleaseComponent();
			GrabObject->OnLaunch();
			GrabObject->LaunchObjet(GetActorForwardVector().GetSafeNormal(), 450.f);
			bIsCarryingSomething = false;
			TouchObjetct = nullptr;
			GrabObject = nullptr;
		}

	}
}

AAInteractiveActor* AUeJam2021Character::GetCurrentHeltObjetc()
{
	return GrabObject;
}

void AUeJam2021Character::RealseObjetc()
{
	PhysicsHandle->ReleaseComponent();
	GrabObject->OnRealesed();
	bIsCarryingSomething = false;
	TouchObjetct = nullptr;
	GrabObject = nullptr;

	
}


void AUeJam2021Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUeJam2021Character::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
