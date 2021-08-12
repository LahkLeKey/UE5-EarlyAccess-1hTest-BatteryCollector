// Copyright Epic Games, Inc. All Rights Reserved.

#include "Battery_CollectorGameMode.h"
//#include "Battery_CollectorCharacter.h"
//#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"

ABattery_CollectorGameMode::ABattery_CollectorGameMode()
{
	//PrimaryActorTick.bCanEverTick = true; // Allow Tick Per Frame
}

/* Override Events */

// Call override
//void ABattery_CollectorGameMode::BeginPlay()
//{
//	Super::BeginPlay();
//
//
//	//FTimerHandle THandle;
//	//GetWorldTimerManager().SetTimer(
//	//	THandle,
//	//	this,
//	//	&ABattery_CollectorGameMode::SpawnPlayerRecharge,
//	//	FMath::RandRange(2, 5),
//	//	true); // Allow Loop
//}

// Call override
//void ABattery_CollectorGameMode::Tick(float DeltaSeconds)
//{
//	Super:Tick(DeltaSeconds);
//}
//
//void ABattery_CollectorGameMode::SpawnPlayerRecharge()
//{
//	// Pick random 2d
//	float RandX = FMath::RandRange(SpawnXMin, SpawnXMax);
//	float RandY = FMath::RandRange(SpawnYMin, SpawnYMax);
//
//	// Use player spawn origin as h and set new spawn.
//	FVector RandPOS = FVector(RandX, RandY, SpawnZ);
//
//	// Initialize normalized rotation
//	FRotator NRot = FRotator(0.0f, 0.0f, 0.0f);
//
//	// Spawn New Batteries
//	GetWorld()->SpawnActor(PlayerRecharge, &RandPOS, &NRot);
//}

