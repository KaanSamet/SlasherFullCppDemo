// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/Weapon.h"
#include "OneHanded.generated.h"

/**
 * 
 */
UCLASS()
class KAANS_GULER_DEMOS_API AOneHanded : public AWeapon
{
	GENERATED_BODY()

protected:
	AOneHanded();
	virtual void ItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void ItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void Item_Interact_Implementation() override;
	virtual void Item_Equip_Implementation(USceneComponent* ParentSceneComponent, FName SocketName) override;
	virtual void Item_AddToInventory_Implementation() override;

};
