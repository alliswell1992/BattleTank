// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();
	/*
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("not controlled tank"));
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("controlled tank is %s"), *ControlledTank->GetName());
	}*/
	auto AmingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AmingComponent) {
		FoundAimingComponent(AmingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("player controlled can't find aming component at begin play"));
	}
}

void AMyPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void AMyPlayerController::AimTowardsCrosshair() {
	if (!ensure(GetControlledTank())) {
		return;
	}
	FVector OutHitLocation;
	if (GetSighRayHitLocation(OutHitLocation)) { //has "side-effect ", is going to line trace
		//UE_LOG(LogTemp, Warning, TEXT("hit location is : %s"), *OutHitLocation.ToString());
		// tell the controlled tank to aim at this position 
		GetControlledTank()->AimAt(OutHitLocation);
	}
	
}
//get world location from crosshair 
bool AMyPlayerController::GetSighRayHitLocation(FVector& OutHitLocation) const {
	// find the crosshair position in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrosshairXLocation, ViewPortSizeY * CrosshairYLocation);
	// de-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("hit direction is : %s"), *LookDirection.ToString());
		// line trace along that look direction, and see what we hit (up to max range) 
		GetLookVectorHitLocation(LookDirection, OutHitLocation);

	}
	return true;
}

bool AMyPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

bool AMyPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation; // to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);



}


ATank* AMyPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}
