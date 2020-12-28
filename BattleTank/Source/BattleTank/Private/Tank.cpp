// Fill out your copyright notice in the Description page of Project Settings.

//#include "Projectile.h"
#include "Tank.h"
//#include "TankAimingComponent.h"
//#include "TankBarrel.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// no need to protect points as added at component
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}
float ATank::GetHealthPercent() const {
	return (float)CurrentHealth / (float)StartingHealth;
}

// Called when the game starts or when spawned
//void ATank::BeginPlay()
//{
//	Super::BeginPlay();// needed for BP begin play to run 
//	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
//}

//void ATank::AimAt(FVector HitLocation) {
//	if (!ensure(TankAimingComponent)) { 
//		return;
//	}
//	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
//}


// Called to bind functionality to input
/*void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTarrelReference(UTankTarrel* TarrelToSet) {
	TankAimingComponent->SetTarrelReference(TarrelToSet);
*/
//
//void ATank::Firing() {
//	if (!ensure(Barrel)) {
//		return;
//	}
//	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
//	if (isReloaded) { //
//		// spawn a projectile at the socket on the barrel
//		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
//		Projectile->LaunchProjectile(LaunchSpeed);
//		LastFireTime = FPlatformTime::Seconds();
//		return;
//	}
//
//
//}
//

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth<=0) {
		//UE_LOG(LogTemp, Warning, TEXT("Tank died"))
		OnDeath.Broadcast();
	}
	return DamageToApply;
}
