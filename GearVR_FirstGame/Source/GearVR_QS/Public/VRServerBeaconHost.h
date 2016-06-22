

#pragma once
#include "Runtime/Online/OnlineSubsystemVRils/Public/OnlineBeaconHost.h"
#include "Runtime/Online/OnlineSubsystemVRils/Public/OnlineBeaconHostObject.h"
#include "VRServerBeaconHost.generated.h"

/**
* A beacon host used for taking reservations for an existing game session
*/
UCLASS(transient, notplaceable, config = Engine)
class UNREALTOURNAMENT_API AVRServerBeaconHost : public AOnlineBeaconHostObject
{
	GENERATED_UCLASS_BODY()

	// Begin AOnlineBeaconHost Interface 
	virtual AOnlineBeaconClient* SpawnBeaconActor(class UNetConnection* ClientConnection) override;
	virtual void ClientConnected(class AOnlineBeaconClient* NewClientActor, class UNetConnection* ClientConnection);
	// End AOnlineBeaconHost Interface 

	virtual bool Init();
};
