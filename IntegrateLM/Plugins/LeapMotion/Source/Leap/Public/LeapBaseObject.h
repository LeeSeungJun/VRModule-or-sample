#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapBaseObject.generated.h"


UCLASS()
class LEAPMOTION_API ULeapBaseObject : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	virtual void CleanupRootReferences() {};
};