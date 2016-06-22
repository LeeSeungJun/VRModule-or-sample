

#pragma once
#include "Runtime/Online/OnlineSubsystemVRils/Public/OnlineBeaconHost.h"
#include "Runtime/Online/OnlineSubsystemVRils/Public/OnlineBeaconHostObject.h"
#include "VRServerBeaconHost.h"
#include "VRServerBeaconLobbyHostObject.generated.h"

UCLASS(transient, notplaceable, config = Engine)
class UNREALTOURNAMENT_API AVRServerBeaconLobbyHostObject : public AVRServerBeaconHost
{
	GENERATED_UCLASS_BODY()
	virtual AOnlineBeaconClient* SpawnBeaconActor(class UNetConnection* ClientConnection) override;
	virtual void ClientConnected(class AOnlineBeaconClient* NewClientActor, class UNetConnection* ClientConnection);

};
