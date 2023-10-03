// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/TwoHanded.h"
#include "Characters/SlashCharacter.h"

ATwoHanded::ATwoHanded()
{
}

void ATwoHanded::ItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ItemBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ATwoHanded::ItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::ItemEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}




void ATwoHanded::Item_Interact_Implementation()
{
	Super::Item_Interact_Implementation();
}

void ATwoHanded::Item_Equip_Implementation(USceneComponent* ParentSceneComponent, FName SocketName)
{
	Super::Item_Equip_Implementation(ParentSceneComponent, SocketName);

	TObjectPtr<ASlashCharacter> SlashCharacter = Cast<ASlashCharacter>(ParentSceneComponent->GetOwner());
	if (SlashCharacter)
	{
		if (!WeaponAttackAnimMontage) 
		{
			GEngine->AddOnScreenDebugMessage(-1, 500.f, FColor::Red, TEXT("YOU FORGOT TO SET THIS WEAPON ATTACKANIMMONTAGE"));
			return;
		}

		SlashCharacter->SetCharacterEquippedState(ECharacterEquippedState::CES_Equipped_TwoHanded);
		SlashCharacter->SetCharacterEquippedWeapon(this);
		SlashCharacter->SetCharacterAttackAnimMontage(WeaponAttackAnimMontage); 

		Item_Equip(ParentSceneComponent, SocketName);
	}
}

void ATwoHanded::Item_AddToInventory_Implementation()
{
	Super::Item_AddToInventory_Implementation();
}
