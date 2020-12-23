// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "Tanktarrel.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called every frame 
/*
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}*/

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	//auto MyName = GetOwner()->GetName();
	if (!Barrel||!Tarrel) {
		return;
	}
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//MoveTarrelTowards(AimDirection);
		MoveBarrelTowards(AimDirection);
		
		//UE_LOG(LogTemp, Warning, TEXT("aiming solution found"));
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("no aiming solution found"));
	}
	
}

void UTankAimingComponent::InitialiseAiming(UTankBarrel* BarrelToSet, UTankTarrel* TarrelToSet) {
	Barrel = BarrelToSet;
	Tarrel = TarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!Barrel || !Tarrel) { return; }
	//work-out difference bettween barrel current rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Tarrel->Rotate(DeltaRotator.Yaw);
}/*
void UTankAimingComponent::MoveTarrelTowards(FVector AimDirection) {
	//work-out difference bettween tarrel current rotation and aim direction
	auto TarrelRotator = Tarrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TarrelRotator;
	Tarrel->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTarrelReference(UTankTarrel* TarrelToSet) {
	Tarrel = TarrelToSet;
}*/

