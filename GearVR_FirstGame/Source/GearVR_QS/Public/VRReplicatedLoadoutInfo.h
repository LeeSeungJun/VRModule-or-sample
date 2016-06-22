
#pragma once

#include "VRATypes.h"
#include "VRReplicatedLoadoVRInfo.generated.h"

UCLASS()
class UNREALTOURNAMENT_API AVRReplicatedLoadoVRInfo : public AInfo
{
	GENERATED_UCLASS_BODY()

	// The weapon
	UPROPERTY(Replicated)
	TSubclassOf<AVRInventory> ItemClass;

	// What rounds are this weapon available in
	UPROPERTY(Replicated)
	uint8 RoundMask;

	UPROPERTY(Replicated)
	uint32 bDefaultInclude:1;

	UPROPERTY(Replicated)
	uint32 bPurchaseOnly:1;

	// What is the current cost of this weapon
	UPROPERTY(Replicated)
	float CurrentCost;

public:

		

};



