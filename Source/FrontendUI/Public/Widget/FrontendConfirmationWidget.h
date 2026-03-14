#pragma once

#include "CoreMinimal.h"
#include "FrontendEnumTypes.h"
#include "Widget/FrontendActivatableWidget.h"
#include "FrontendConfirmationWidget.generated.h"

class UCommonTextBlock;
class UDynamicEntryBox;

USTRUCT(BlueprintType)
struct FRONTENDUI_API FConfirmationButtonInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ButtonText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConfirmationScreenButtonType ButtonType;
};

UCLASS()
class FRONTENDUI_API UConfirmationScreenInfoObject : public UObject
{
	GENERATED_BODY()

public:
	static UConfirmationScreenInfoObject* CreateOkScreenInfo(const FText& InConfirmationTitle,
	                                                         const FText& InConfirmationMessage);
	static UConfirmationScreenInfoObject* CreateYesNoScreenInfo(const FText& InConfirmationTitle,
	                                                            const FText& InConfirmationMessage);
	static UConfirmationScreenInfoObject* CreateOkCancelScreenInfo(const FText& InConfirmationTitle,
	                                                               const FText& InConfirmationMessage);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ConfirmationTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ConfirmationMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FConfirmationButtonInfo> ConfirmationButtons;
};

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UFrontendConfirmationWidget : public UFrontendActivatableWidget
{
	GENERATED_BODY()

public:
	void InitConfirmScreen(const UConfirmationScreenInfoObject* InConfirmScreenObject,
	                       TFunction<void(EConfirmationScreenButtonType)> InClickedCallback);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> TitleTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> MessageTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> ConfirmButtonBox;
};
