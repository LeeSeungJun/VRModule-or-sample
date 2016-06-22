
#pragma once

#include "VRDuelGame.h"

#include "VRShowdownGame.generated.h"

UCLASS()
class UNREALTOURNAMENT_API AVRShowdownGame : public AVRDuelGame
{
	GENERATED_BODY()
protected:
	/** used to deny RestartPlayer() except for our forced spawn at round start */
	bool bAllowPlayerRespawns;

	virtual void HandleMatchIntermission();
	UFUNCTION()
	virtual void StartIntermission();

	virtual void HandleMatchHasStarted() override;
	virtual void StartNewRound();

	// experimental tiebreaker options
	// will be removed once we decide on a path
	UPROPERTY(config)
	bool bXRayBreaker; // both players see others through walls after 60 seconds
	UPROPERTY(config)
	bool bPowerupBreaker; // spawn super powerup at 60 seconds

	UPROPERTY(EditDefaultsOnly, Meta = (MetaClass = "VRPickupInventory"))
	FStringClassReference PowerupBreakerPickupClass;
	UPROPERTY(EditDefaultsOnly, Meta = (MetaClass = "VRTimedPowerup"))
	FStringClassReference PowerupBreakerItemClass;
	/** item that replaces superweapons (Redeemer, etc) */
	UPROPERTY(EditDefaultsOnly, Meta = (MetaClass = "VRPickupInventory"))
	FStringClassReference SuperweaponReplacementPickupClass;
	UPROPERTY(EditDefaultsOnly, Meta = (MetaClass = "VRInventory"))
	FStringClassReference SuperweaponReplacementItemClass;

	UPROPERTY()
	AVRPickupInventory* BreakerPickup;
public:
	AVRShowdownGame(const FObjectInitializer& OI);

	/** extra health added to players */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ExtraHealth;

	/** time in seconds for players to choose spawn points */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 SpawnSelectionTime;

	/** players that still need to pick their spawn points after current player */
	UPROPERTY(BlueprintReadOnly)
	TArray<AVRPlayerState*> RemainingPicks;

	/** elapsed time in the current round */
	UPROPERTY(BlueprintReadOnly)
	int32 RoundElapsedTime;

	/** team that won last round */
	UPROPERTY(BlueprintReadOnly)
	AVRTeamInfo* LastRoundWinner;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	virtual bool CheckRelevance_Implementation(AActor* Other) override;
	virtual void SetPlayerDefaults(APawn* PlayerPawn) override;
	virtual void ScoreKill_Implementation(AController* Killer, AController* Other, APawn* KilledPawn, TSubclassOf<UDamageType> DamageType) override;
	virtual void RestartPlayer(AController* aPlayer) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual float RatePlayerStart(APlayerStart* P, AController* Player) override;

	virtual void CheckGameTime() override;
	/** score round that ended by timelimit instead of by kill */
	virtual void ScoreExpiredRoundTime();
	virtual void CallMatchStateChangeNotify() override;
	virtual void DefaultTimer() override;

	// Creates the URL options for custom games
	virtual void CreateGameURLOptions(TArray<TSharedPtr<TAttribVRePropertyBase>>& MenuProps);

#if !UE_SERVER
	virtual void CreateConfigWidgets(TSharedPtr<class SVerticalBox> MenuSpace, bool bCreateReadOnly, TArray< TSharedPtr<TAttribVRePropertyBase> >& ConfigProps) override;
#endif
};
