

#pragma once
#include "Commandlets/Commandlet.h"
#include "VRResetPostProcessVolumesCommandlet.generated.h"

UCLASS()
class UVRResetPostProcessVolumesCommandlet : public UCommandlet
{
	GENERATED_UCLASS_BODY()

	// Begin UCommandlet Interface
	virtual int32 Main(const FString& Params) override;
	// End UCommandlet Interface
};