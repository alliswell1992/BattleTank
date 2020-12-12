// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"


void  ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("not AI controlled tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controlled tank is %s"), *ControlledTank->GetName());
	}
	auto PlayerTank = GetPLayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controlled can't find PlayerTank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controlled find PlayerTank is %s"), *PlayerTank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPLayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}
