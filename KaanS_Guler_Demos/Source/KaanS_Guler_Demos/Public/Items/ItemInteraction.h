// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInteraction.generated.h"

UINTERFACE(MinimalAPI)
class UItemInteraction : public UInterface
{
	GENERATED_BODY()
};


class KAANS_GULER_DEMOS_API IItemInteraction
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Item_Interact();

	UFUNCTION(BlueprintNativeEvent)
	void Item_Equip(USceneComponent* ParentSceneComponent, FName SocketName);

	UFUNCTION(BlueprintNativeEvent)
	void Item_AddToInventory();
};
