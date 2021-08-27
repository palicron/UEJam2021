// Copyright Epic Games, Inc. All Rights Reserved.

#include "UeJam2021Character.h"

#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "TimerManager.h"


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

	PlayerInputComponent->BindAxis("MoveForward", this, &AUeJam2021Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUeJam2021Character::MoveRight);


}

void AUeJam2021Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CheckGround();
	AddPushDownForce();
	CheckMaxPressJump(DeltaSeconds);
	
}

void AUeJam2021Character::MakeDash()
{
	//TODO Force depending of velocity
	if(canDash)
	{
		FVector direction = GetActorForwardVector();
		direction.Z = 0;
		
		if (isGrounded)
		{
			LaunchCharacter(direction.GetSafeNormal() * 1200.f, false, false);
		}
		else
		{
			LaunchCharacter(direction.GetSafeNormal() * 500.f, false, true);
		}
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
	if(!isGrounded && !bIsJumping)
	{
		GetCharacterMovement()->AddForce(GetActorUpVector() * -300000.f);
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
	if ( (Controller != nullptr) && (Value != 0.0f) )
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
