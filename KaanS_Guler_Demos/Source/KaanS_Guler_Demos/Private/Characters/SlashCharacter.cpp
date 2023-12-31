// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "Characters/SlashCharacter.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Items/Item.h"
#include "Items/Weapons/OneHanded.h"
#include "Items/Weapons/TwoHanded.h"
#include "Items/Weapons/Weapon.h"

#include "EnhancedInputSubsystems.h"
#include "GroomComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimInstance.h"


// Sets default values
ASlashCharacter::ASlashCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 300.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh(), FName("head"));
	//Hair->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("head"));

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh(), FName("head"));
	//Eyebrows->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("head"));
	//Eyebrows->SetupAttachment(GetMesh());
}



// Called when the game starts or when spawned
void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	/*
	FTransform HairCorrectionTransform = FTransform(FRotator(-190.02f, -190.f, -190.02f), FVector(152.3f, 0.f, 0.f), FVector::OneVector);
	FTransform EyebrowsCorrectionTransform = FTransform(FRotator(-90.f, -349.76f, 349.76f), FVector(152.3f, 0.f, 0.f), FVector::OneVector);

	Hair->SetRelativeTransform(HairCorrectionTransform);
	Eyebrows->SetRelativeTransform(EyebrowsCorrectionTransform);
	*/
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	// Add mapping context
	if (PlayerController)
	{
		// Get local player subsystem
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(SlashCharacterInputMappingContext, 0); //0 priority
		}
	}
}


// Called every frame
void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TrackCharacterGameplayState();

	/*
	if (bCharacterInputAllowance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("true"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("false"));
	}
	*/
	

	/*
	if (GEngine)
	{
		FString Message = FString::Printf(TEXT("CharacterGameplayState = %s"), *UEnum::GetValueAsString(GetCharacterGameplayState()));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, Message);
	}
	*/

	/*
	const FVector HairLocation = Hair->GetComponentLocation();
	const FVector HeadSocketLocation = GetMesh()->GetSocketLocation(TEXT("head"));

	FString HairLocationString = HairLocation.ToString();
	FString HeadSocketLocationString = HeadSocketLocation.ToString();

	FString Message = FString::Printf(TEXT("Hair Location : %s Head Location : %s"), *HairLocationString, *HeadSocketLocationString);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, Message);
	}
	*/
}

// Called to bind functionality to input
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(SlashCharacterInputAction_WASD, ETriggerEvent::Triggered, this, &ThisClass::MoveWASD);
		EnhancedInputComponent->BindAction(SlashCharacterInputAction_LookAround, ETriggerEvent::Triggered, this, &ThisClass::LookAround);
		EnhancedInputComponent->BindAction(SlashCharacterInputAction_Interact, ETriggerEvent::Triggered, this, &ThisClass::Interact);
		EnhancedInputComponent->BindAction(SlashCharacterInputAction_Attack, ETriggerEvent::Triggered, this, &ThisClass::Attack);
	}

}

void ASlashCharacter::AttachWeaponToHand_ForBlueprint()
{
	TObjectPtr<AWeapon> CharacterEquippedWeapon = GetCharacterEquippedWeapon();

	if(!CharacterEquippedWeapon)
	{
		return;
	}

	AttachWeaponToHand(CharacterEquippedWeapon);
}

void ASlashCharacter::DetachWeaponFromHand_ForBlueprint()
{
	TObjectPtr<AWeapon> CharacterEquippedWeapon = GetCharacterEquippedWeapon();

	if (!CharacterEquippedWeapon)
	{
		return;
	}

	DetachWeaponFromHand(CharacterEquippedWeapon);
}

void ASlashCharacter::AttachWeaponToHand(TObjectPtr<AWeapon> Weapon)
{

}

void ASlashCharacter::DetachWeaponFromHand(TObjectPtr<AWeapon> Weapon)
{

}

void ASlashCharacter::TrackCharacterGameplayState()
{
	bool bCharacterIsFalling = GetCharacterMovement()->IsFalling();
	float CharacterVelocity = UKismetMathLibrary::VSizeXY(GetCharacterMovement()->Velocity);

	if (bCharacterIsFalling)
	{
		SetCharacterGameplayState(ECharacterGameplayState::CGS_Jumping);
	}
	else if (!bCharacterIsFalling && (CharacterVelocity != 0))
	{
		SetCharacterGameplayState(ECharacterGameplayState::CGS_Running);
	}
	else if (!bCharacterIsFalling && (CharacterVelocity == 0))
	{
		SetCharacterGameplayState(ECharacterGameplayState::CGS_Idle);
	}
}		

// -------------------------------------------------- Input Functions -------------------------------------------------- 

void ASlashCharacter::MoveWASD(const FInputActionValue& Value)
{
	if (GetController() && bCharacterInputAllowance) 
	{
		switch (GetCharacterGameplayState())
		{
			case (ECharacterGameplayState::CGS_Idle):
			case (ECharacterGameplayState::CGS_Jumping):
			case (ECharacterGameplayState::CGS_Running):
			{
				const float MoveForwardValue = (Value.Get<FVector>()).X;
				const float MoveRightValue = (Value.Get<FVector>()).Y;
				const float JumpValue = (Value.Get<FVector>()).Z;
				FRotator ControlRotation = GetControlRotation();

				/*
				UE_LOG(LogTemp, Warning, TEXT("MoveForwardValue: %f"), MoveForwardValue)
				UE_LOG(LogTemp, Warning, TEXT("MoveRightValue: %f"), MoveRightValue)
				UE_LOG(LogTemp, Warning, TEXT("JumpValue: %f"), JumpValue)
				*/

				if (MoveForwardValue != 0)
				{
					FVector MoveDirection = FRotationMatrix(FRotator(0.f, ControlRotation.Yaw, 0.f)).GetUnitAxis(EAxis::X);
					AddMovementInput(MoveDirection, MoveForwardValue);
				}
				if (MoveRightValue != 0)
				{
					FVector MoveDirection = FRotationMatrix(FRotator(0.f, ControlRotation.Yaw, 0.f)).GetUnitAxis(EAxis::Y);
					AddMovementInput(MoveDirection, MoveRightValue);
				}
				if (JumpValue != 0)
				{
					ACharacter::Jump();
				}
				break;
			}
		}
		
	}
}

void ASlashCharacter::LookAround(const FInputActionValue& Value)
{
	const FVector2D LookAroundValue = Value.Get<FVector2D>();
	const float LookAroundYaw = LookAroundValue.X;
	const float LookAroundPitch = (LookAroundValue.Y)*-1;

	AddControllerYawInput(LookAroundYaw);
	AddControllerPitchInput(LookAroundPitch);
}

void ASlashCharacter::Interact(const FInputActionValue& Value)
{
	if (!bCharacterInputAllowance) return;

	const float Grab = (Value.Get<FVector>()).X;
	const float Drop = (Value.Get<FVector>()).Y;
	const float SwitchMode = (Value.Get<FVector>()).Z;

	if (Grab != 0)
	{
		if (OverlappedItems.Num() == 0)
		{
			return;
		}

		for (TObjectPtr<AItem> ThisItem : OverlappedItems)
		{
			IItemInteraction* ThisItemInterface = Cast<IItemInteraction>(ThisItem);

			if (ThisItemInterface)
			{
				EquipWeaponOrAddToInventory(ThisItem, ThisItemInterface);
			}

			
		}
	}

	if (Drop != 0)
	{
		
	}

	if (SwitchMode != 0)
	{
		if (!GetCharacterEquippedWeapon())
		{
			return;
		}
		
		TObjectPtr<AWeapon> CharacterCurrentEquippedWeapon = GetCharacterEquippedWeapon();
		EWeaponType ThisWeaponType = CharacterCurrentEquippedWeapon->GetWeaponType();
		TObjectPtr <UAnimInstance> AnimInstance = GetMesh()->GetAnimInstance();

		if (!(CharacterCurrentEquippedWeapon && AnimInstance))
		{
			return;
		}

		switch (ThisWeaponType)
		{
			case(EWeaponType::EWT_None):
			{
				break;
			}

			case(EWeaponType::EWT_OneHanded):
			{
				break;
			}
		}
	}
}

void ASlashCharacter::EquipWeaponOrAddToInventory(TObjectPtr<AItem> ThisOverlappedItem, IItemInteraction* ThisOverlappedItemInterface)
{
	ThisOverlappedItemInterface->Execute_Item_Equip(ThisOverlappedItem, GetMesh(), FName("RightHandOneHandedWeaponSocket"));

	
	/*
	TObjectPtr<AWeapon> OverlappingWeapon = Cast<AWeapon>(ThisOverlappedItem);

	if (!OverlappingWeapon) return;

	switch (CharacterEquippedState)
	{
		case ECharacterEquippedState::CES_UnEquipped:
		{
			// Weapon Related Getters
			AttackAnimMontage = OverlappingWeapon->GetAnimMontage();

			//One Handed Related Getters
			OverlappingWeapon = Cast<AOneHanded>(OverlappingWeapon);
			if (OverlappingWeapon)
			{
				OverlappingWeapon->Execute_Item_Equip(GetMesh(), FName("RightHandOneHandedWeaponSocket")); //Give Socket Name For The One Handeds
				CharacterEquippedState = ECharacterEquippedState::CES_Equipped_OneHanded;
				SetCharacterEquippedWeapon(OverlappingWeapon);
			}

			// Two Handed Related Getters
			OverlappingWeapon = Cast<ATwoHanded>(OverlappingWeapon);
			if (OverlappingWeapon)
			{
				OverlappingWeapon->EquipWeapon(GetMesh(), FName("RightHandOneHandedWeaponSocket")); //Give Socket Name For The Two Handeds
				CharacterEquippedState = ECharacterEquippedState::CES_Equipped_TwoHanded;
				SetCharacterEquippedWeapon(OverlappingWeapon);
			}

		}
		case ECharacterEquippedState::CES_Equipped_OneHanded:
		case ECharacterEquippedState::CES_Equipped_TwoHanded:
		{
			break; //Add the weapon to inventory
		}
	}
	*/
}

void ASlashCharacter::Attack(const FInputActionValue& Value)
{
	if (!bCharacterInputAllowance) return;

	const bool AttackValue = Value.Get<bool>();
	if (AttackValue)
	{
		switch (CharacterGameplayState)
		{
			case (ECharacterGameplayState::CGS_Idle):
			{
				Play_StandingBasicAttackMontage();
				break;
			}
			case(ECharacterGameplayState::CGS_Jumping):
			case(ECharacterGameplayState::CGS_Running):
			{
				break;
			}
		}
	}
}



void ASlashCharacter::Play_StandingBasicAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackAnimMontage)
	{
		switch (CharacterEquippedState)
		{
		case (ECharacterEquippedState::CES_UnEquipped):
		{
			break;
		}
		case (ECharacterEquippedState::CES_Equipped_OneHanded):
		{
			AnimInstance->Montage_Play(AttackAnimMontage);
			AnimInstance->Montage_SetPlayRate(AttackAnimMontage, 1.5f);
			int32 SelectedMontageSection = FMath::RandRange(0, 10);
			FName MontageSection = FName();
			switch (SelectedMontageSection)
			{
			case 0: case 1: case 2:
				MontageSection = FName("Attack1");
				break;
			case 3:
				MontageSection = FName("Attack2");
				break;
			case 4: case 5: case 6:
				MontageSection = FName("Attack3");
				break;
			case 7: case 8: case 9:
				MontageSection = FName("Attack4");
				break;
			case 10:
				MontageSection = FName("Attack5");
				break;
			}
			AnimInstance->Montage_JumpToSection(MontageSection, AttackAnimMontage);
		}
		case (ECharacterEquippedState::CES_Equipped_TwoHanded):
		{
			break;
		}
		}
	}
}



