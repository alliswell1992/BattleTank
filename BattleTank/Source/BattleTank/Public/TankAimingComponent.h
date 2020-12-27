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
	Locked,
	OutOfAmmo
};
// forward declaration
class UTankBarrel; 
class UTankTarrel;
class AProjectile;
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
	void AimAt(FVector HitLocation);//, float LaunchSpeed);
	//void SetBarrelReference(UTankBarrel* BarrelToSet);
	//void SetTarrelReference(UTankTarrel* TarrelToSet);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitialiseAiming(UTankBarrel* BarrelToSet, UTankTarrel* TarrelToSet);
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Firing();
	EFireStatus GetFireState();
	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundLeft() const;
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	// Sets default values for this component's properties
	UTankAimingComponent();
	bool IsBarrelMoving();
	UTankBarrel* Barrel = nullptr;
	UTankTarrel* Tarrel = nullptr;
	void MoveBarrelTowards();
	//void MoveTarrelTowards(FVector); 
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000.;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundLeft = 3;
	double LastFireTime = 0;
	FVector AimDirection;

};
