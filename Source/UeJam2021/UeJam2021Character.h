// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UeJam2021Character.generated.h"
class AAInteractiveActor;
class UTexture2D;
UCLASS(config=Game)
class AUeJam2021Character : public ACharacter
{
	GENERATED_BODY()

public:
	AUeJam2021Character();

protected:



	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);



protected:

	FTimerHandle DashTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movment Stats")
		float DashCd = 1.0f;

	float  JumpHoldTime = 0;

	 AAInteractiveActor* TouchObjetct = nullptr;

	 AAInteractiveActor* GrabObject = nullptr;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	virtual void Tick(float DeltaSeconds) override;

	void ResetDash();

	void CheckGround();

	void MakeDash();

	virtual void Jump() override;

	virtual void StopJumping() override;;

	void AddPushDownForce();

	void CheckMaxPressJump(float DeltaTime);

	void CheckForObjets();

	void TryToInteract();

	void LaunchGrabItem();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		class UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movment Stats")
		float DashMulty = 2.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movment Stats")
	bool isGrounded = false;

	bool canDash = true;

	bool bIsJumping = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movment Stats")
	bool bIsCarryingSomething = false;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Items")
		void OnInteractOnrange(AAInteractiveActor* inter);
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, Category = "Items")
		void OnRealeseOnrange();

	UFUNCTION(BlueprintCallable)
		AAInteractiveActor* GetCurrentHeltObjetc();
	UFUNCTION(BlueprintCallable)
		void RealseObjetc();
	UFUNCTION(BlueprintPure)
		AAInteractiveActor* currentTouchItem() const;
	UFUNCTION(BlueprintPure)
		AAInteractiveActor* currentPickItem() const;
	UFUNCTION(BlueprintPure)
		bool CanObjetBelauch() const;
	UFUNCTION(BlueprintPure)
		UTexture2D*  GetCurrentImage() const;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		FVector spherelocation;
};

