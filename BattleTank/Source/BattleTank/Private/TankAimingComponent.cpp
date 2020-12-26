// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "Tanktarrel.h"
#include "Projectile.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}
void UTankAimingComponent::BeginPlay() {
	//first fire is after reload
	LastFireTime = FPlatformTime::Seconds();
}
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	if (RoundLeft <= 0) {
		FireStatus = EFireStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FireStatus = EFireStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FireStatus = EFireStatus::Aming;
	}
	else {
		FireStatus = EFireStatus::Locked;
	}
}
bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) {
		return false;
	}
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

// Called every frame 
/*
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}*/

void UTankAimingComponent::AimAt(FVector HitLocation) {
	//auto MyName = GetOwner()->GetName();
	
	if (!ensure(Barrel)) {
		return;
	}
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		//MoveTarrelTowards(AimDirection);

		MoveBarrelTowards();
		
		//UE_LOG(LogTemp, Warning, TEXT("aiming solution found"));
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("no aiming solution found"));
	}
	
}
void UTankAimingComponent::Firing() {

	//UE_LOG(LogTemp, Warning, TEXT("firing "));
	if (FireStatus == EFireStatus::Locked || FireStatus == EFireStatus::Aming) { //
		if (!ensure(Barrel && ProjectileBlueprint)) {
			return;
		}
		// spawn a projectile at the socket on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundLeft--;
		return;
	}


}


void UTankAimingComponent::InitialiseAiming(UTankBarrel* BarrelToSet, UTankTarrel* TarrelToSet) {
	Barrel = BarrelToSet;
	Tarrel = TarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards() {
	if (!Barrel || !Tarrel) { return; }
	
	//work-out difference bettween barrel current rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Tarrel->Rotate(DeltaRotator.Yaw);
	}
	else {
		Tarrel->Rotate(-DeltaRotator.Yaw);
	}
	
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
EFireStatus UTankAimingComponent::GetFireState() {
	return FireStatus;
}

int UTankAimingComponent::GetRoundLeft() const {
	return RoundLeft;
}

