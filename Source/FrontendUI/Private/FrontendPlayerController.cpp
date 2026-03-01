#include "FrontendPlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AFrontendPlayerController::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);

	TArray<AActor*> Cameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(
		this, ACameraActor::StaticClass(), FName("Default"), Cameras);

	if (!Cameras.IsEmpty())
	{
		SetViewTarget(Cameras[0]);
	}
}
