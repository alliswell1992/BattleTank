// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 80000.;
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//ATank* GetControlledTank() const;
	//ATank* GetPLayerTank() const;
	// how close can ai tank get
	UFUNCTION()
	void OnPossedTankDeath();
	virtual void SetPawn(APawn* InPawn) override;
};
