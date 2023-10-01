// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInteraction.h"

#include "Item.generated.h"

class USphereComponent;

UCLASS()
class KAANS_GULER_DEMOS_API AItem : public AActor, public IItemInteraction
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void Tick(float DeltaTime) override;

	


protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void ItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void ItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh;

	virtual void Item_Equip(USceneComponent* ParentSceneComponent, FName SocketName);

	//Interface functions
	virtual void Item_Interact_Implementation() override;
	virtual void Item_Equip_Implementation(USceneComponent* ParentSceneComponent, FName SocketName) override;
	virtual void Item_AddToInventory_Implementation() override;

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCollision;

};
