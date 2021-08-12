// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABatteryMan::ABatteryMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Generate Collision Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Set Camera > Player Rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Allow Character to orient in the direction that it is moving.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Add Spring Arm Component with the name CameraBoom to the root component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);


	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true; // Pass Boom Rotation to Controller

	// Add Camera with name FollowCamera to the root component
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	// Attach Follow Camera to the Camera Boom at the end of the boom. Allowing the boom to adjust the rotation
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Disable camera rotation relative to arm.
	FollowCamera->bUsePawnControlRotation = false;

	bDead = false; // Should not initialize as UCE-Dead
	Power = 100.0f; // Always start supercharged
}


// Called when the game starts or when spawned
void ABatteryMan::BeginPlay()
{
	Super::BeginPlay();

	// Bind Component Events

	// OnBeginOverlap Event
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABatteryMan::OnBeginOverlap);

	// Render Power Widget Event
	if(Player_Power_Widget_Class != nullptr)
	{
		Player_Power_Widget = CreateWidget(GetWorld(), Player_Power_Widget_Class);
		Player_Power_Widget->AddToViewport();
	}
	
}

// Called every frame
void ABatteryMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update Power Stat
	Power -= DeltaTime * PowerT;

	// Death
	if (Power <= 0)
	{
		if (!bDead)
		{
			bDead = true;

			// Time to ragdoll
			GetMesh()->SetSimulatePhysics(true);
			FTimerHandle THandle;
			GetWorldTimerManager().SetTimer(
				THandle,
				this,
				&ABatteryMan::RestartLevel,
				3.0f,
				false);
		}
	}
}

// Called to bind functionality to input
void ABatteryMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind camera access to project setting controller7

	// Mouse X Camera
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	// Mouse Y Camera
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Bind Jump on press
	PlayerInputComponent->BindAction("Jump",  IE_Pressed, this, &ACharacter::Jump);

	// Bind StopJump on release
	PlayerInputComponent->BindAction("Jump",  IE_Released, this, &ACharacter::StopJumping);

	// Bind Forward / Backward to override
	PlayerInputComponent->BindAxis("MoveForward", this, &ABatteryMan::MoveForward);

	// Bind Right / Left to override
	PlayerInputComponent->BindAxis("MoveRight", this, &ABatteryMan::MoveRight);
}

void ABatteryMan::MoveForward(float Axis)
{
	if (!bDead)
	{
		// Get Rotation from Controller
		const FRotator Rotation = Controller->GetControlRotation();

		// Filter Rotation for forward direction (Yaw)
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Calculate forward direction of vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Add results to the forward movement input
		AddMovementInput(Direction, Axis);
	}

}

void ABatteryMan::MoveRight(float Axis)
{
	// Get Rotation from Controller
	const FRotator Rotation = Controller->GetControlRotation();

	// Filter Rotation for forward direction (Yaw)
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// Calculate right direction of vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Add results to the right movement input
	AddMovementInput(Direction, Axis);
}


void ABatteryMan::RestartLevel()
{
	UGameplayStatics::OpenLevel(this,
		FName(*GetWorld()->GetName()), // Get name of current world.
		false);
}


void ABatteryMan::OnBeginOverlap(
	UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Recharge"))
	{
		// UE_LOG(LogTemp, Warning, TEXT("Collision Detected ::"))

		Power += 10.0f;

		// Prevent Supercharging
		if (Power > 100.0f) Power = 100.0f;

		OtherActor->Destroy(); // Consume Battery
	}
}