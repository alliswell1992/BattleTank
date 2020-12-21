// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) {
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("intent move forward: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	return;
	// TODO prevent double speed due to control use
}
void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) {
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("intent move forward: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	return;
	// TODO prevent double speed due to control use
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	// no need to call super as we're replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AiForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AiForwardIntention);
	UE_LOG(LogTemp, Warning, TEXT(" vectoring to"))
	IntendMoveForward(ForwardThrow);

}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
