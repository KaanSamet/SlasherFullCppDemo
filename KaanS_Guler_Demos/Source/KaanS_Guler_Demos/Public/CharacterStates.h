#pragma once

UENUM(BlueprintType)
enum class ECharacterEquippedState : uint8
{
	CES_UnEquipped UMETA(DisplayName = "Unequipped"),
	CES_Equipped_OneHanded UMETA(DisplayName = "EquippedOneHandedWeapon"),
	CES_Equipped_TwoHanded UMETA(DisplayName = "EqippedTwoHandedWeapon")
};

UENUM(BlueprintType)
enum class ECharacterGameplayState : uint8
{
	CGS_Idle UMETA(DisplayName = "Idle"),
	CGS_Running UMETA(DisplayName = "Running"),
	CGS_Jumping UMETA(DisplayName = "Jumping")
};