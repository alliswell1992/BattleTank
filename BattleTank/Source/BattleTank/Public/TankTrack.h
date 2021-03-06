// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	//set a throttle between 1 and -1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throtile); 
	// max force per trace in newtons
private:
	UTankTrack();
	virtual void BeginPlay() override;
	TArray<class ASprungWheel*> GetWheels() const;
	//void ApplySidewayForce();
	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulsem, const FHitResult& Hit);
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TraceMaxDrivingFroce = 40000000.; // assume 40000 kg(40 tonne) tank , and 10 m per second per second(1g) accelleration
	void DriveTrack(float CurrentThrotile);
};
