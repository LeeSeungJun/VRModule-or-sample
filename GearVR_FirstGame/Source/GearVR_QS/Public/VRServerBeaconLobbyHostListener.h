

#pragma once
#include "Runtime/Online/OnlineSubsystemVRils/Public/OnlineBeaconHost.h"
#include "Runtime/Online/OnlineSubsystemVRils/Public/OnlineBeaconHostObject.h"
#include "VRServerBeaconLobbyHostObject.h"
#include "VRServerBeaconLobbyHostListener.generated.h"

UCLASS(transient, notplaceable, config = Engine)
class UNREALTOURNAMENT_API AVRServerBeaconLobbyHostListener : public AOnlineBeaconHost
{
	GENERATED_UCLASS_BODY()
};
