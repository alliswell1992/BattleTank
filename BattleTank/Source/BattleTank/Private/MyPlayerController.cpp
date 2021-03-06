// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
//#include "Tank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
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
	if (!GetPawn()) return;
	auto AmingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AmingComponent)) {
		return;
	}
	/*else {
		UE_LOG(LogTemp, Warning, TEXT("player controlled can't find aming component at begin play"));
	}*/
	FoundAimingComponent(AmingComponent);
}

void AMyPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void AMyPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; }
	auto AmingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AmingComponent)) {
		return;
	}
	FVector OutHitLocation;
	if (GetSighRayHitLocation(OutHitLocation)) { //has "side-effect ", is going to line trace
		//UE_LOG(LogTemp, Warning, TEXT("hit location is : %s"), *OutHitLocation.ToString());
		// tell the controlled tank to aim at this position 
		AmingComponent->AimAt(OutHitLocation);
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
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);

	}
	return false;
}
void AMyPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) {
			return;
		}
		// subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &AMyPlayerController::OnPossedTankDeath);
	}
}
void AMyPlayerController::OnPossedTankDeath() {
	StartSpectatingOnly();
}

bool AMyPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera)) {
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

//
//ATank* AMyPlayerController::GetControlledTank() const {
//	return GetPawn();
//}
