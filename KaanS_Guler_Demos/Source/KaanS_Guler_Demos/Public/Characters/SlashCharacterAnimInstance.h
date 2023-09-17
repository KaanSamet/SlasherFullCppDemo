// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterStates.h"

#include "SlashCharacterAnimInstance.generated.h"

class ASlashCharacter;
class UCharacterMovementComponent;


UCLASS()
class KAANS_GULER_DEMOS_API USlashCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	ASlashCharacter* SlashCharacter;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	UCharacterMovementComponent* SlashCharacterMovementComponent;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CharacterGroundSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsFalling;
	UPROPERTY(BlueprintReadOnly, Category = "CharacterStates")
	ECharacterEquippedState CharacterEquippedState = ECharacterEquippedState::CES_UnEquipped;
	UPROPERTY(BlueprintReadOnly, Category = "CharacterStates")
	ECharacterGameplayState CharacterGameplayState = ECharacterGameplayState::CGS_Idle;
	
};
