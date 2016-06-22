#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapBone.generated.h"

UCLASS(BlueprintType)
class LEAPMOTION_API ULeapBone : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapBone();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FMatrix Basis;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FVector Center;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FVector Direction;


	UFUNCTION(BlueprintCallable, Category = "Leap Bone")
	FRotator GetOrientation(LeapHandType HandType);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	bool IsValid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	float Length;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FVector NextJoint;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FVector PrevJoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	TEnumAsByte<LeapBoneType> Type;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	float Width;



	UFUNCTION(BlueprintCallable, meta = (DisplayName = "different", CompactNodeTitle = "!=", Keywords = "different operator"), Category = "Leap Bone")
	bool Different(const ULeapBone *other) const;


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "equal", CompactNodeTitle = "==", Keywords = "equal operator"), Category = "Leap Bone")
	bool Equal(const ULeapBone *other) const;

	void SetBone(const class Leap::Bone &bone);

private:
	class PrivateBone* Private;
};