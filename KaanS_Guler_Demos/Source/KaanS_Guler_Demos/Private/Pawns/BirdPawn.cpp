// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BirdPawn.h"

//Component headers
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

//Enhanced Input headers
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"

ABirdPawn::ABirdPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	
	BirdCapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BirdCollisionCapsule"));
	SetRootComponent(BirdCapsuleCollision);
	BirdCapsuleCollision->SetCapsuleHalfHeight(20.f);
	BirdCapsuleCollision->SetCapsuleRadius(15.f);

	BirdSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdSkeletalMesh"));
	BirdSkeletalMesh->SetupAttachment(GetRootComponent());;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 300.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ABirdPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	// Add mapping context
	if (PlayerController)
	{
		// Get local player subsystem
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(BirdInputMappingContext, 0); //0 priority
		}
	}
}


void ABirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(BirdInputAction_ForwardMove, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(BirdInputAction_TurnAround, ETriggerEvent::Triggered, this, &ThisClass::TurnAround);
	}
	
	//PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ThisClass::MoveForward);

}

// -------------------------------------------------- Input Functions -------------------------------------------------- 

void ABirdPawn::Move(const FInputActionValue& Value)
{
	const float CurrentValue = Value.Get<float>();

	if (GetController() && (CurrentValue != 0))
	{
		FVector PawnForwardVector = GetActorForwardVector();
		AddMovementInput(PawnForwardVector, CurrentValue);
	}
}

void ABirdPawn::TurnAround(const FInputActionValue& Value)
{
	const FVector2D LookAroundValue = Value.Get<FVector2D>();

	if (GetController()) 
	{
		AddControllerYawInput(LookAroundValue.X);
		AddControllerPitchInput(LookAroundValue.Y);
	}
	
}
