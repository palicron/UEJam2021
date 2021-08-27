// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

//Get force to move in DashVelosity in XY plane 
FVector UMyBlueprintFunctionLibrary::GetLaunchForceHorizontal(FVector direction, FVector Velocity, float HorizontalDistan, float Mass
	, float DashVelocity,float time)
{
	FVector finalVector = direction.GetSafeNormal() * HorizontalDistan;


	UE_LOG(LogTemp, Warning, TEXT("Vel %s" ),*Velocity.ToString());
	float Xforce = ((2 * Mass) * (((DashVelocity* direction.GetSafeNormal().X) * time) - finalVector.X) / FMath::Pow(time, 2));
	float Yforce = ((2 * Mass) * (((DashVelocity * direction.GetSafeNormal().Y) * time) - finalVector.Y) / FMath::Pow(time, 2));
	UE_LOG(LogTemp, Warning, TEXT("X force %f and Y force %f"), Xforce,Yforce);
	return FVector(Xforce, Yforce, 0);
}
