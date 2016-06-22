

#pragma once

#include "LeapBlueprintFunctionLibrary.generated.h"


UCLASS()
class ULeapBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()


	UFUNCTION(BlueprintCallable, Category = "Leap Motion Functions")
	static void EnableTimeWarp(bool Enable = true, float Factor = 1.f, float Tween = 1.f);


	UFUNCTION(BlueprintPure, Category = "Leap Motion Functions")
	static void GetHMDFieldOfView(float& OutHFOVInDegrees, float& OutVFOVInDegrees);

	UFUNCTION(BlueprintPure, Category = "Leap Motion Functions")
	static void GetTimewarpStats(bool& OutEnabled, float& OutFactor, float& OutTimeWarpAmountMs);
};