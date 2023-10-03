// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/OneHanded.h"
#include "Characters/SlashCharacter.h"

AOneHanded::AOneHanded()
{
}

void AOneHanded::ItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ItemBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AOneHanded::ItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::ItemEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}


// Interface Functions
void AOneHanded::Item_Interact_Implementation()
{
	Super::Item_Interact_Implementation();
}

void AOneHanded::Item_Equip_Implementation(USceneComponent* ParentSceneComponent, FName SocketName)
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

		SlashCharacter->SetCharacterEquippedState(ECharacterEquippedState::CES_Equipped_OneHanded);
		SlashCharacter->SetCharacterEquippedWeapon(this);
		SlashCharacter->SetCharacterAttackAnimMontage(WeaponAttackAnimMontage);

		Item_Equip(ParentSceneComponent, SocketName);
	}
}

void AOneHanded::Item_AddToInventory_Implementation()
{
	Super::Item_AddToInventory_Implementation();
}