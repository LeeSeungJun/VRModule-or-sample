#pragma once

#include "AnimBone.h"
#include "LeapEnums.h"
#include "AnimFinger.generated.h"


UENUM(BlueprintType)
enum AnimHandType
{
	ANIM_HAND_UNKNOWN,
	ANIM_HAND_LEFT,
	ANIM_HAND_RIGHT
};

UCLASS(BlueprintType)
class LEAPMOTION_API UAnimFinger : public UObject
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Anim Finger")
	UAnimBone* Metacarpal;


	UPROPERTY(BlueprintReadOnly, Category = "Anim Finger")
	UAnimBone* Proximal;


	UPROPERTY(BlueprintReadOnly, Category = "Anim Finger")
	UAnimBone* Intermediate;

	UPROPERTY(BlueprintReadOnly, Category = "Anim Finger")
	UAnimBone* Distal;


	UPROPERTY(BlueprintReadWrite, Category = "Anim Finger")
	float Alpha;


	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	bool Enabled();


	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void SetEnabled(bool Enable = true);


	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void TranslateFinger(FVector Shift);


	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void TransformFinger(FTransform& ByTransform);


	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void ChangeBasis(FRotator PreBase, FRotator PostBase, bool AdjustVectors = true);


	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void SetFromLeapFinger(class ULeapFinger* Finger, LeapHandType HandType);
};