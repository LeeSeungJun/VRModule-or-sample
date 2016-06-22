#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapInteractionBox.generated.h"


UCLASS(BlueprintType)
class LEAPMOTION_API ULeapInteractionBox : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapInteractionBox();
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	FVector Center;


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DenormalizePoint", CompactNodeTitle = "", Keywords = "normalize point"), Category = "Leap Interaction Box")
	FVector DenormalizePoint(FVector Position) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	float Depth;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	bool IsValid;


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "normalizePoint", CompactNodeTitle = "", Keywords = "normalize point"), Category = "Leap Interaction Box")
	FVector NormalizePoint(FVector Position, bool Clamp=true) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	float Width;

	void SetInteractionBox(const class Leap::InteractionBox &InteractionBox);

private:
	class PrivateInteractionBox* Private;
};