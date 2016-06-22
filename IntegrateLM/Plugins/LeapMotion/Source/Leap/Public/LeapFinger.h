#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapPointable.h"
#include "LeapFinger.generated.h"


UCLASS(BlueprintType)
class LEAPMOTION_API ULeapFinger : public ULeapPointable
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapFinger();


	UFUNCTION(BlueprintCallable, meta = (Category = "Leap Finger"))
	class ULeapBone *Bone(enum LeapBoneType Type);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger")
	class ULeapBone *Metacarpal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger")
	class ULeapBone *Proximal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger")
	class ULeapBone *Intermediate;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger")
	class ULeapBone *Distal;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger")
	TEnumAsByte<LeapFingerType> Type;

	void SetFinger(const class Leap::Finger &Pointable);

private:
	class PrivateFinger* Private;
};