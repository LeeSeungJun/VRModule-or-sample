#pragma once

#include "LeapPrivatePCH.h"
#include "IInputDevice.h"


struct LeapControllerData
{
	//Reference to the Leap Controller base
	Leap::Controller LeapController;

	//Public custom controller toggles
	bool bAllowImageEvents = false;
	bool bOptimizeForHMD = false;
	bool bUseGammaCorrection = false;
	bool bImageEventsEnabled = false;
	bool bUseMountOffset = true;
	bool bTimeWarpEnabled = false;	//v 2.0.1 disable timewarp until it works correctly
	float TimeWarpAmountMs = 0.f;	//In milliseconds
	float TimeWarpFactor = 1.f;	//0-1.f magnitude of timewarp applied
	float TimeWarpTween = 1.f;
	LeapHMDSnapshot TimeWarpSnapshot;	//latest timewarp snapshot
};

class FLeapInputDevice : public IInputDevice
{
public:
	FLeapInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& MessageHandler);


	virtual void Tick(float DeltaTime) override;


	virtual void SendControllerEvents() override;

	void ParseEvents();


	virtual void SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override;


	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;


	virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
	virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values) override;

	virtual ~FLeapInputDevice();

	TSharedRef< FGenericApplicationMessageHandler > MessageHandler;

	LeapControllerData ControllerData;
	
	void AddEventDelegate(UObject* EventDelegate);
	void RemoveEventDelegate(UObject* EventDelegate);

private:
	//Private UProperties
	void ClearReferences(UObject* object);
	class ULeapBaseObject* PRoot = nullptr;
	class ULeapHand* PEventHand = nullptr;
	class ULeapFinger* PEventFinger = nullptr;
	class ULeapGesture* PEventGesture = nullptr;
	class ULeapCircleGesture* PEventCircleGesture = nullptr;
	class ULeapKeyTapGesture* PEventKeyTapGesture = nullptr;
	class ULeapScreenTapGesture* PEventScreenTapGesture = nullptr;
	class ULeapSwipeGesture* PEventSwipeGesture = nullptr;
	class ULeapImage* PEventImage1 = nullptr;
	class ULeapImage* PEventImage2 = nullptr;

	class LeapStateData* PastState;			//state handling
	TArray<UObject*> EventDelegates;		//delegate storage
	class HMDSnapshotSamples* HMDSamples;	//timewarp

	//Private utility methods
	void CallFunctionOnDelegates(TFunction< void(UObject*)> InFunction);	//lambda multi-cast convenience wrapper
	bool EmitKeyUpEventForKey(FKey Key, int32 User, bool Repeat);
	bool EmitKeyDownEventForKey(FKey Key, int32 User, bool Repeat);
	bool EmitAnalogInputEventForKey(FKey Key, float Value, int32 User, bool Repeat);
	bool HandClosed(float Strength);
	bool HandPinched(float Strength);
	bool HandForId(int32 CheckId, Leap::HandList Hands, Leap::Hand& ReturnHand);
};