#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrontendPlayerController.generated.h"

UCLASS()
class FRONTENDUI_API AFrontendPlayerController : public APlayerController {
  GENERATED_BODY()

protected:
  //~Begin APlayerController Interface
  virtual void OnPossess(APawn *Pawn) override;
  //~End APlayerController Interface
};
