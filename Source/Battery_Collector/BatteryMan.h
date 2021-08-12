// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "BatteryMan.generated.h"

UCLASS()
class BATTERY_COLLECTOR_API ABatteryMan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABatteryMan();

	// Spring Arm Component with the name CameraBoom
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	// Camera with name FollowCamera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	// Movement Functions
	void MoveForward(float Axis);
	void MoveRight(float Axis);

	// Unique Character Booleans

	// UCB, Is the character dead?
	bool bDead;

	// Unique Character Stats

	// UCS, Character current Power stat
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Power;

	// UCS, Character Power Threshold
	UPROPERTY(EditAnywhere) 
		float PowerT;

	// UCE, OnBeginOverlap
	UFUNCTION()
		void OnBeginOverlap(
			class UPrimitiveComponent* HitComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);


	/* Requires "UMG" in PublicDependencyModuleNames.AddRange[Battery_Collecter.Build.cs] */
	// Power Widget Properties
	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<UUserWidget> Player_Power_Widget_Class;

	// Power Widget
	UUserWidget* Player_Power_Widget;

	// Restart Game
	void RestartLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
