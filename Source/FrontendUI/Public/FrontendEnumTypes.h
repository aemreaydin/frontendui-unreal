#pragma once

UENUM(BlueprintType)
enum class EConfirmationScreenType : uint8
{
	Ok,
	YesNo,
	OkCancel,
	Unknown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EConfirmationScreenButtonType : uint8
{
	Confirm,
	Cancel,
	Close,
	Unknown UMETA(Hidden)
};
