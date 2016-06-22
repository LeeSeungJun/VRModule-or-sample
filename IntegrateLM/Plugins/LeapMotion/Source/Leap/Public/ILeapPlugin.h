
#pragma once

#include "LeapMotionPublicPCH.h"
#include "ILeapMotionPlugin.h"
#include "IInputDeviceModule.h"




class LEAPMOTION_API ILeapMotionPlugin : public IInputDeviceModule
{

public:


	static inline ILeapMotionPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked< ILeapMotionPlugin >( "LeapMotion" );
	}

	
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "LeapMotion" );
	}

	
	virtual struct LeapControllerData* ControllerData(){ return nullptr; };
	
	virtual void AddEventDelegate(UObject* EventDelegate) {};

	virtual void RemoveEventDelegate(UObject* EventDelegate) {};
};

