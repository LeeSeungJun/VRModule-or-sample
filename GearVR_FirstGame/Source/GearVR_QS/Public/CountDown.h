
#pragma once

#include "GameFramework/Actor.h"
#include "CountDown.generated.h"

UCLASS()
class FIRST_API ACountDown : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	ACountDown();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	int32 CountdownTime;

	//int32 CountdownTime;
	VRextRenderComponent* CountdownText;
	//FTimerHandle CountdownTimerHandle;

	//void UpdateTimerDisplay();
	//void AdvanceTimer();
	//void CountdownHasFinished();
	
	//How long, in seconds, the countdown will run
	
	/*
	int32 CountdownTime;
	
	VRextRenderComponent* CountdownText;

	void UpdateTimerDisplay();

	void AdvanceTimer();

	void CountdownHasFinished();

	FTimerHandle CountdownTimerHandle;
	*/
	
};
