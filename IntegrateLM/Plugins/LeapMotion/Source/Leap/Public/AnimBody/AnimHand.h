#pragma once

#include "AnimFinger.h"
#include "LeapHand.h"
#include "AnimHand.generated.h"


UCLASS(BlueprintType)
class LEAPMOTION_API UAnimHand : public UObject
{
	GENERATED_UCLASS_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim Hand")
	float Alpha;


	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand Hand")
	float Confidence;

	//Fingers


	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand Finger")
	UAnimFinger* Thumb;


	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand Finger")
	UAnimFinger* Index;
	

	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand Finger")
	UAnimFinger* Middle;


	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand Finger")
	UAnimFinger* Ring;

	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand Finger")
	UAnimFinger* Pinky;
	

	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand")
	UAnimBone* Wrist;


	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand")
	UAnimBone* Palm;
	

	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand")
	UAnimBone* LowerArm;


	UFUNCTION(BlueprintCallable, Category = "Anim Hand")
	bool Enabled();


	UFUNCTION(BlueprintCallable, Category = "Anim Hand")
	void SetEnabled(bool Enable = true);


	UFUNCTION(BlueprintCallable, Category = "Anim Hand")
	void TranslateHand(FVector Shift);


	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void TransformHand(FTransform& ByTransform);


	UFUNCTION(BlueprintCallable, Category = "Anim Hand")
	void ChangeBasis(FRotator PreBase, FRotator PostBase, bool AdjustVectors = true);



	UFUNCTION(BlueprintCallable, Category = "Anim Hand")
	void SetFromLeapHand(class ULeapHand* LeapHand);


	UFUNCTION(BlueprintCallable, Category = "Anim Hand")
	void ApplyTimewarp();
};