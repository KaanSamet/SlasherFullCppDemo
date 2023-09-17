#pragma once
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_None UMETA(DisplayName = "None"),
	EWT_OneHanded UMETA(DisplayName = "OneHanded"),
	EWT_TwoHanded UMETA(DisplayName = "TwoHanded")
};