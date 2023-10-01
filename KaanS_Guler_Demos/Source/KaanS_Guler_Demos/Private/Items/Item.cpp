// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "KaanS_Guler_Demos/DebugMacros.h"
#include "Components/SphereComponent.h"
#include "Characters/SlashCharacter.h"
#include "GameFramework/Character.h"


AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	ItemMesh->SetCollisionProfileName(FName("NoCollision"));
	RootComponent = ItemMesh;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(ItemMesh);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ItemBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::ItemEndOverlap);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::ItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if (SlashCharacter)
	{
		SlashCharacter->AddOverlappedItem(this);
	}
}

void AItem::ItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if (SlashCharacter)
	{
		SlashCharacter->RemoveOverlappedItem(this);
	}
}


void AItem::Item_Equip(USceneComponent* ParentSceneComponent, FName SocketName)
{
	AttachToComponent(ParentSceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
	GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, TEXT("AITEM EQUIP"));
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


//Interface Functions
void AItem::Item_Interact_Implementation()
{

}

void AItem::Item_Equip_Implementation(USceneComponent* ParentSceneComponent, FName SocketName)
{

}

void AItem::Item_AddToInventory_Implementation()
{

}