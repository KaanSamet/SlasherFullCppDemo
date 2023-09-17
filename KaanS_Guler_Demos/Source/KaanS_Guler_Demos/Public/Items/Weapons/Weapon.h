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

public:
	UFUNCTION()
	void EquipWeapon(USceneComponent* ParentSceneComponent, FName SocketName);

protected:
	UPROPERTY(VisibleAnywhere, Category = "WeaponType")
	EWeaponType WeaponType = EWeaponType::EWT_None;

public:
	UFUNCTION(BlueprintPure, Category = "CoreWeaponFunctions")
	virtual EWeaponType GetWeaponType()
	{
		return WeaponType;
	}

	UFUNCTION(BlueprintCallable, Category = "CoreWeaponFunctions")
	virtual void SetWeaponType(EWeaponType InputWeaponType)
	{
		WeaponType = InputWeaponType;
	}
};
