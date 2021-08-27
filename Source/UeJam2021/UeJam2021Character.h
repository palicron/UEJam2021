// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UeJam2021Character.generated.h"

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
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	virtual void Tick(float DeltaSeconds) override;

	void MakeDash();

	FTimerHandle DashTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movment Stats")
		float DashCd = 1.0f;

	void ResetDash();

	void CheckGround();

	virtual void Jump() override;

	virtual void StopJumping() override;;

	void AddPushDownForce();

	void CheckMaxPressJump(float DeltaTime);

	float  JumpHoldTime = 0;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movment Stats")
		float DashMulty = 2.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movment Stats")
	bool isGrounded = false;

	bool canDash = true;

	bool bIsJumping = false;
};

