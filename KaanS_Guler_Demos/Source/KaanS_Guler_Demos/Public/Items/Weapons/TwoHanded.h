// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/Weapon.h"
#include "TwoHanded.generated.h"

/**
 * 
 */
UCLASS()
class KAANS_GULER_DEMOS_API ATwoHanded : public AWeapon
{
	GENERATED_BODY()
	
protected:
	ATwoHanded();
	virtual void ItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void ItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* TwoHandedAttackAnimMontage;

public:
	FORCEINLINE UAnimMontage* GetAnimMontage() { return TwoHandedAttackAnimMontage; }

};