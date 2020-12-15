// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Rotate(float RelativeSpeed);
private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreePerSecond = 25; // sensible defaut
};
