#include "FrontendPlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AFrontendPlayerController::OnPossess(APawn *Pawn) {
  Super::OnPossess(Pawn);

  TArray<AActor *> Cameras;
  UGameplayStatics::GetAllActorsOfClassWithTag(
      this, ACameraActor::StaticClass(), FName("Default"), Cameras);

  if (!Cameras.IsEmpty()) {
    SetViewTarget(Cameras[0]);
  }
}