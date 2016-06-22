#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapPointable.h"
#include "LeapTool.generated.h"


UCLASS(BlueprintType)
class LEAPMOTION_API ULeapTool : public ULeapPointable
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapTool();

	void SetTool(const class Leap::Tool &Tool);

private:
	class PrivateTool* Private;
};