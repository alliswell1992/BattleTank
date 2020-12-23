// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
// fire status
UENUM()
enum class EFireStatus : uint8 {
	Reloading,
	Aming,
	Locked
};
// forward declaration
class UTankBarrel; 
class UTankTarrel;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	// Called when the game starts
	//virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFireStatus FireStatus = EFireStatus::Aming;
public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimAt(FVector HitLocation, float LaunchSpeed);
	//void SetBarrelReference(UTankBarrel* BarrelToSet);
	//void SetTarrelReference(UTankTarrel* TarrelToSet);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitialiseAiming(UTankBarrel* BarrelToSet, UTankTarrel* TarrelToSet);
private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	UTankBarrel* Barrel = nullptr;
	UTankTarrel* Tarrel = nullptr;
	void MoveBarrelTowards(FVector);
	//void MoveTarrelTowards(FVector); 
};
