// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
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
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();//Cast<ATank>(GetPawn());
	auto AmingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(PlayerTank&&ControlledTank)) {
		return;
	}
	// move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);
	// aim towards the player
	AmingComponent->AimAt(PlayerTank->GetActorLocation());
	if (AmingComponent->GetFireState() == EFireStatus::Locked) {
		AmingComponent->Firing();//TODO limit fire rate
	}
	 

	//GetControlledTank()->AimAt(GetPLayerTank()->GetActorLocation());
	//fire if ready
	//GetControlledTank()->Firing();

}
void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) {
			return;
		}
		// subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}
void ATankAIController::OnPossedTankDeath() {
	//UE_LOG(LogTemp,Warning, TEXT("received!"))
	if (!ensure(GetPawn())) {
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
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
