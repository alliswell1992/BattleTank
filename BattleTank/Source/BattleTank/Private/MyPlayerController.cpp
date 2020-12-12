// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"



void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("not controlled tank"));
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("controlled tank is %s"), *ControlledTank->GetName());
	}
}

void AMyPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void AMyPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		return;
	}
	//get world location from crosshair 
}

ATank* AMyPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}
