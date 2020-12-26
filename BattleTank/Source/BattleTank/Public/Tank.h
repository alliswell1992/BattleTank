// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//class UTankBarrel;
//class UTankAimingComponent;
//class UTankTarrel;
//class AProjectile;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/*UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;*/
	//UPROPERTY(BlueprintReadOnly)
	//UTankMovementComponent* TankMovementComponent = nullptr;

public:	

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//UFUNCTION(BlueprintCallable, Category = "BPFunc_Lib")
/*	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTarrelReference(UTankTarrel* TarrelToSet); */
/*	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000.; */// sensible starting value of 1000 m/s000000
	//UFUNCTION(BlueprintCallable, Category = "Setup")
	//void Firing();
	// Sets default values for this pawn's properties
	ATank();
	//void AimAt(FVector HitLocation);
private:

	//UTankBarrel* Barrel = nullptr;
	//UPROPERTY(EditDefaultsOnly, Category = "Firing")
	//float ReloadTimeInSeconds = 3;
	//double LastFireTime = 0;
};
