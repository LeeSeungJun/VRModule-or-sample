
#pragma once

#include "VRGameState.h"

#include "VRShowdownGameState.generated.h"

UCLASS()
class UNREALTOURNAMENT_API AVRShowdownGameState : public AVRGameState
{
	GENERATED_UCLASS_BODY()

	/** if in round intermission, player selecting spawn point */
	UPROPERTY(BlueprintReadOnly, Replicated)
	AVRPlayerState* SpawnSelector;
	/** Time remaining in current intermission stage (post-round delay or spawn choice timer) */
	UPROPERTY(BlueprintReadOnly, Replicated)
	uint8 IntermissionStageTime;
	/** set during intermission after spawn selection is started */
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool bStartedSpawnSelection;
	/** set during final countdown before next round begins */
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool bFinalIntermissionDelay;

	/** turns on seeing enemies through walls for all players */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_XRayVision)
	bool bActivateXRayVision;

	bool IsAllowedSpawnPoint_Implementation(AVRPlayerState* Chooser, APlayerStart* DesiredStart) const override;

	UFUNCTION()
	virtual void OnRep_XRayVision();

	virtual void OnRep_MatchState() override;
};