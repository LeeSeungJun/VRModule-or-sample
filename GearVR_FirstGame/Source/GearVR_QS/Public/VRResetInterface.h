// implement this interface for Actors that should handle game mode resets (halftime in CTF, role swap in Assault, etc)

#pragma once

#include "VRResetInterface.generated.h"

UINTERFACE(MinimalAPI)
class UVRResetInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UNREALTOURNAMENT_API IVRResetInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Game)
	void Reset();
};
