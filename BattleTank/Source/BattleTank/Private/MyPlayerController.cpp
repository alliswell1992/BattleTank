// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

ATank* AMyPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}