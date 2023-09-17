// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"

#include "BirdPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;


class UInputMappingContext;
class UInputAction;


UCLASS()
class KAANS_GULER_DEMOS_API ABirdPawn : public APawn
{
	GENERATED_BODY()

public:
	ABirdPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* BirdInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* BirdInputAction_ForwardMove;
	void Move(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* BirdInputAction_TurnAround;
	void TurnAround(const FInputActionValue& Value);

private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* BirdCapsuleCollision;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BirdSkeletalMesh;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
};