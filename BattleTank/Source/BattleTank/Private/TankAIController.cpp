// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void  ATankAIController::BeginPlay() {
	Super::BeginPlay();
	/*
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
	}*/
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (!(PlayerTank&&ControlledTank)) {
		return;
	}
	// move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);
	// aim towards the player
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Firing(); //TODO limit fire rate

	//GetControlledTank()->AimAt(GetPLayerTank()->GetActorLocation());
	//fire if ready
	//GetControlledTank()->Firing();

}
/*
ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPLayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}*/
