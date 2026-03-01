#pragma once

namespace Frontend::Debug
{
	FORCEINLINE void Log(const FString& Msg, const uint64 Key = -1, const FColor Color = FColor::MakeRandomColor())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(Key, 5.0F, Color, Msg);
		}
	}
}
