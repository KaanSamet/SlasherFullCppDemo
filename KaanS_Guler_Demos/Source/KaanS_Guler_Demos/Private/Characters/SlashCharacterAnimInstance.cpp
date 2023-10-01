// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashCharacterAnimInstance.h"
#include "Characters/SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CharacterStates.h"

void USlashCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());

	if (SlashCharacter)
	{
		SlashCharacterMovementComponent = SlashCharacter->GetCharacterMovement();
	}
	
}

void USlashCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (SlashCharacterMovementComponent)
	{
		CharacterGroundSpeed = UKismetMathLibrary::VSizeXY(SlashCharacterMovementComponent->Velocity);
		IsFalling = SlashCharacterMovementComponent->IsFalling();
		CharacterEquippedState = SlashCharacter->GetCharacterEquippedState();
		CharacterGameplayState = SlashCharacter->GetCharacterGameplayState();
	}
}
