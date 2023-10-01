// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"
#include "Characters/SlashCharacter.h"
#include "GameFramework/Character.h"

AWeapon::AWeapon()
{
}

void AWeapon::ItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ItemBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::ItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::ItemEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}


// Interface Functions
void AWeapon::Item_Interact_Implementation()
{
	Super::Item_Interact_Implementation();
}

void AWeapon::Item_Equip_Implementation(USceneComponent* ParentSceneComponent, FName SocketName)
{
	Super::Item_Equip_Implementation(ParentSceneComponent, SocketName);
}

void AWeapon::Item_AddToInventory_Implementation()
{
	Super::Item_AddToInventory_Implementation();
}
