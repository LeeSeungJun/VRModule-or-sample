

#pragma once

#include "LeapPrivatePCH.h"
#include "../Public/ILeapPlugin.h"


class FLeapPlugin : public ILeapPlugin
{
public:
	virtual TSharedPtr< class IInputDevice > CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler);

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual struct LeapControllerData* ControllerData() override;
	virtual void AddEventDelegate(UObject* EventDelegate) override;
	virtual void RemoveEventDelegate(UObject* EventDelegate) override;

	bool IsActive();

	TSharedPtr< class FLeapInputDevice > LeapInputDevice;

private:
	bool bActive = false;
};
