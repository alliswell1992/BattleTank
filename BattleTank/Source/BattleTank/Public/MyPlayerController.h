// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class ATank;
UCLASS()
class BATTLETANK_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank* GetControlledTank() const;
	// move the tank tarrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();
	// return an out parameter, true if hit landscape
	bool GetSighRayHitLocation(FVector& OutHitLocation) const;
	UPROPERTY(EditAnyWhere)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnyWhere)
	float CrosshairYLocation = 0.3333f;
	bool GetLookDirection(FVector2D, FVector&) const;
	UPROPERTY(EditAnyWhere)
	float LineTraceRange = 1000000.f;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
