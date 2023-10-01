// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "WeaponEnums.h"

#include "Weapon.generated.h"


/**
 * 
 */
UCLASS()
class KAANS_GULER_DEMOS_API AWeapon : public AItem
{
	GENERATED_BODY()

protected:
	AWeapon();
	virtual void ItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void ItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "WeaponType")
	EWeaponType WeaponType = EWeaponType::EWT_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* WeaponAttackAnimMontage;

	virtual void Item_Interact_Implementation() override;
	virtual void Item_Equip_Implementation(USceneComponent* ParentSceneComponent, FName SocketName) override;
	virtual void Item_AddToInventory_Implementation() override;

public:
	/*
	** BlueprintCallable setters
	*/
	UFUNCTION(BlueprintPure, Category = "CoreWeaponFunctions")
	virtual EWeaponType GetWeaponType()
	{
		return WeaponType;
	}

	/*
	** BlueprintCallable mutators
	*/
	UFUNCTION(BlueprintCallable, Category = "CoreWeaponFunctions")
	virtual void SetWeaponType(EWeaponType InputWeaponType)
	{
		WeaponType = InputWeaponType;
	}

	/*
	** Inline setters
	*/
	FORCEINLINE UAnimMontage* GetAnimMontage() { return WeaponAttackAnimMontage; }
};
