// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

#include "SprungWheel.h"
#include "SpawnPoint.h"
UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}
void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	//OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

//void UTankTrack::ApplySidewayForce() {
//	// calculate slippagespeed
//	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
//	// work-out required acceleration this frame to corret
//	auto DeltaTime = GetWorld()->GetDeltaSeconds();
//	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
//	//calculate and apply sideways (f= m a)
//	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
//	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // two tracks
//	TankRoot->AddForce(CorrectionForce);
//}
void UTankTrack::SetThrottle(float Throtile) {
	float CurrentThrotile = FMath::Clamp<float>(Throtile, -1, 1);
	DriveTrack(CurrentThrotile);
}
//( FComponentHitSignature, UPrimitiveComponent, OnComponentHit, UPrimitiveComponent*, HitComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, FVector, NormalImpulse, const FHitResult&, Hit );
//void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulsem, const FHitResult& Hit) {
//	//UE_LOG(LogTemp, Warning, TEXT("on hit"));
//	DriveTrack();
//	ApplySidewayForce();
//	CurrentThrotile = 0;
//}
void UTankTrack::DriveTrack(float CurrentThrotile) {
	auto ForceApplied =  CurrentThrotile * TraceMaxDrivingFroce;
	//auto ForceLocation = GetComponentLocation();
	//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	//UE_LOG(LogTemp, Warning, TEXT("set throtile: %f"), Throtile);
	auto Wheels = GetWheels();
	for (ASprungWheel* Wheel : Wheels) {
		Wheel->AddDriverForce(ForceApplied / Wheels.Num());
	}

}
TArray<ASprungWheel*> UTankTrack::GetWheels() const{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (auto Child : Children) {
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;
		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;
		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}