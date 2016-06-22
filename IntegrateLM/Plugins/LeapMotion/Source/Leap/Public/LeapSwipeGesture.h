#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapGesture.h"
#include "LeapSwipeGesture.generated.h"

UCLASS(BlueprintType)
class LEAPMOTION_API ULeapSwipeGesture : public ULeapGesture
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapSwipeGesture();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	TEnumAsByte<LeapBasicDirection> BasicDirection;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	FVector Direction;


	UFUNCTION(BlueprintCallable, Category = "Leap Swipe Gesture")
	class ULeapPointable* Pointable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	float Speed;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	FVector StartPosition;
	
	void SetGesture(const class Leap::SwipeGesture &Gesture);

private:
	class PrivateSwipeGesture* Private;

	UPROPERTY()
	ULeapPointable* PPointable = nullptr;
};