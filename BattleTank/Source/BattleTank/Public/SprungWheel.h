// CopyRight EmbraceIT LTD.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"
class UPhysicsConstraintComponent;
class USphereComponent;
UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AddDriverForce(float ForceMagnitude);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	void SetupConstraint();
	//Components
	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//UStaticMeshComponent* Mass = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Axle = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* MassWheelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
};