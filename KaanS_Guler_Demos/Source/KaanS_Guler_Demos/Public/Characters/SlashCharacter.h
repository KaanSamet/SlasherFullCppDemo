// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterStates.h"
#include "WeaponEnums.h"

#include "SlashCharacter.generated.h"


class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UGroomComponent;
class AItem;
class AWeapon;
class IItemInteraction;




UCLASS()
class KAANS_GULER_DEMOS_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Animations")
	void AttachWeaponToHand_ForBlueprint();

	UFUNCTION(BlueprintCallable, Category="Animations")
	void DetachWeaponFromHand_ForBlueprint();


	void EquipWeaponOrAddToInventory(TObjectPtr<AItem> ThisOverlappedItem, IItemInteraction* ThisOverlappedItemInterface);


protected: //BlueprintCalledFunction calls cpp based functions
	void AttachWeaponToHand(TObjectPtr<AWeapon> Weapon);
	void DetachWeaponFromHand(TObjectPtr<AWeapon> Weapon);
	UFUNCTION()
	void Play_StandingBasicAttackMontage();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr <UInputMappingContext> SlashCharacterInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr <UInputAction> SlashCharacterInputAction_WASD;
	void MoveWASD(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr <UInputAction> SlashCharacterInputAction_LookAround;
	void LookAround(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr <UInputAction> SlashCharacterInputAction_Interact;
	void Interact(const FInputActionValue& Value);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr <UInputAction> SlashCharacterInputAction_Attack;
	void Attack(const FInputActionValue& Value);

	UPROPERTY(VisibleInstanceOnly)
	TArray<AItem*> OverlappedItems;

	UFUNCTION()
	void TrackCharacterGameplayState();


private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr <UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr <USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Hair")
	TObjectPtr <UGroomComponent> Hair;

	UPROPERTY(VisibleAnywhere, Category = "Hair")
	TObjectPtr <UGroomComponent> Eyebrows;

	UPROPERTY(VisibleAnywhere, Category = "Animations")
	TObjectPtr <UAnimMontage> AttackAnimMontage;

	UPROPERTY(VisibleAnywhere, Category = "Animations")
	TObjectPtr <UAnimMontage> SwitchWeaponAnimMontage;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	TObjectPtr <AWeapon> EquippedWeapon = nullptr;

	ECharacterEquippedState CharacterEquippedState = ECharacterEquippedState::CES_UnEquipped;

	UPROPERTY(BlueprintReadWrite, Category="CharacterState", meta=(AllowPrivateAccess = "true"))
	ECharacterGameplayState CharacterGameplayState = ECharacterGameplayState::CGS_Idle;

	UPROPERTY(BlueprintReadWrite, Category = "CharacterState", meta = (AllowPrivateAccess = "true"))
	bool bCharacterInputAllowance = true;

public:
	//------------------------------- GETTERS -------------------------------
	/**
	* Inline getters
	*/
	FORCEINLINE void AddOverlappedItem(AItem* Item) { OverlappedItems.AddUnique(Item); }
	FORCEINLINE void RemoveOverlappedItem(AItem* Item) { OverlappedItems.Remove(Item); }
	FORCEINLINE ECharacterEquippedState GetCharacterEquippedState() const { return CharacterEquippedState; }
	FORCEINLINE TObjectPtr<AWeapon> GetCharacterEquippedWeapon() const { return EquippedWeapon; }
	/**
	* UFUNC getters
	*/
	UFUNCTION(BlueprintPure)
	ECharacterGameplayState GetCharacterGameplayState() { return CharacterGameplayState; }
	UFUNCTION(BlueprintPure)
	bool GetCharacterInputAllowance() { return bCharacterInputAllowance; }

	//------------------------------- SETTERS -------------------------------
	/**
	* Inline mutators
	*/
	FORCEINLINE void SetCharacterEquippedWeapon(AWeapon* CharacterEquippedWeapon) { EquippedWeapon = CharacterEquippedWeapon; }
	FORCEINLINE void SetCharacterEquippedState(ECharacterEquippedState ECharacterEquippedState) { CharacterEquippedState = ECharacterEquippedState; }
	/**
	* UFUNC mutators
	*/
	UFUNCTION(BlueprintCallable)
	void SetCharacterGameplayState(ECharacterGameplayState CharacterGameplayState_Set) { CharacterGameplayState = CharacterGameplayState_Set; }
	UFUNCTION(BlueprintCallable)
	void SetCharacterInputAllowance(bool NewCharacterInputAllowance) { bCharacterInputAllowance = NewCharacterInputAllowance; }
};
