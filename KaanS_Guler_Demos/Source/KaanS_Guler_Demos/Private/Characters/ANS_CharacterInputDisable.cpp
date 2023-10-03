// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ANS_CharacterInputDisable.h"
#include "Characters/SlashCharacter.h"

void UANS_CharacterInputDisable::NotifyBegin(USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Notify Begin"));

	if (!SlashCharacter)
	{
		SlashCharacter = Cast<ASlashCharacter>(MeshComp->GetOwner());
		if (SlashCharacter)
		{
			SlashCharacter->SetCharacterInputAllowance(false);
		}
	}
}

void UANS_CharacterInputDisable::NotifyTick(USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Notify Tick"));
}

void UANS_CharacterInputDisable::NotifyEnd(USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Notify End"));

	if (SlashCharacter)
	{
		SlashCharacter->SetCharacterInputAllowance(true);
		SlashCharacter = nullptr;
	}
}
