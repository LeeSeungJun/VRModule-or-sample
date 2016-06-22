#pragma once

#include "LeapHand.h"
#include "LeapEventInterface.generated.h"

UINTERFACE(MinimalAPI)
class ULeapEventInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class LEAPMOTION_API ILeapEventInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "HandMoved", CompactNodeTitle = "", Keywords = "hand moved"), Category = "Leap Interface Event")
	void LeapHandMoved(ULeapHand* Hand);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "LeftHandMoved", CompactNodeTitle = "", Keywords = "left hand moved"), Category = "Leap Interface Event")
	void LeapLeftHandMoved(ULeapHand* Hand);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "RightHandMoved", CompactNodeTitle = "", Keywords = "right hand moved"), Category = "Leap Interface Event")
	void LeapRightHandMoved(ULeapHand* Hand);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "HandGrabbed", CompactNodeTitle = "", Keywords = "hand grab"), Category = "Leap Interface Event")
	void LeapHandGrabbed(float Strength, ULeapHand* Hand);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "HandGrabbing", CompactNodeTitle = "", Keywords = "hand grab"), Category = "Leap Interface Event")
	void LeapHandGrabbing(float Strength, ULeapHand* Hand);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "HandReleased", CompactNodeTitle = "", Keywords = "hand released ungrab"), Category = "Leap Interface Event")
	void LeapHandReleased(float Strength, ULeapHand* Hand);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "HandPinched", CompactNodeTitle = "", Keywords = "hand pinch"), Category = "Leap Interface Event")
	void LeapHandPinched(float Strength, ULeapHand* Hand);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "HandPinching", CompactNodeTitle = "", Keywords = "hand grab"), Category = "Leap Interface Event")
	void LeapHandPinching(float Strength, ULeapHand* Hand);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "HandUnpinched", CompactNodeTitle = "", Keywords = "hand unpinch"), Category = "Leap Interface Event")
	void LeapHandUnpinched(float Strength, ULeapHand* Hand);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "HandCountChanged", CompactNodeTitle = "", Keywords = "hand count"), Category = "Leap Interface Event")
	void HandCountChanged(int32 Count);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "FingerMoved", CompactNodeTitle = "", Keywords = "finger moved"), Category = "Leap Interface Event")
	void LeapFingerMoved(ULeapFinger* Finger);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "FrontFingerMoved", CompactNodeTitle = "", Keywords = "finger front most moved"), Category = "Leap Interface Event")
	void LeapFrontMostFingerMoved(ULeapFinger* Finger);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "LeftFingerMoved", CompactNodeTitle = "", Keywords = "finger left most moved"), Category = "Leap Interface Event")
	void LeapRightMostFingerMoved(ULeapFinger* Finger);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "RightFingerMoved", CompactNodeTitle = "", Keywords = "finger right most moved"), Category = "Leap Interface Event")
	void LeapLeftMostFingerMoved(ULeapFinger* Finger);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "LeapFrontFingerTouch", CompactNodeTitle = "", Keywords = "finger touched"), Category = "Leap Interface Event")
	void LeapFrontFingerTouch(ULeapFinger* Finger);		//emitted only for frontmost finger, typically best use case

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "FingerCountChanged", CompactNodeTitle = "", Keywords = "finger count"), Category = "Leap Interface Event")
	void FingerCountChanged(int32 Count);

	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "GestureDetected", CompactNodeTitle = "", Keywords = "gesture detect"), Category = "Leap Interface Event")
	void GestureDetected(ULeapGesture* Gesture);

	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "gesture circle detect"), Category = "Leap Interface Event")
	void CircleGestureDetected(ULeapCircleGesture* Gesture);


	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "gesture key tap detect"), Category = "Leap Interface Event")
	void KeyTapGestureDetected(ULeapKeyTapGesture* Gesture);


	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "gesture screen tap detect"), Category = "Leap Interface Event")
	void ScreenTapGestureDetected(ULeapScreenTapGesture* Gesture);


	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "gesture swipe detect"), Category = "Leap Interface Event")
	void SwipeGestureDetected(ULeapSwipeGesture* Gesture);

	
	UFUNCTION(BlueprintImplementableEvent, Category = "Leap Interface Event")
	void RawImageReceived(UTexture2D* Texture, ULeapImage* Image);


	virtual FString ToString();
};