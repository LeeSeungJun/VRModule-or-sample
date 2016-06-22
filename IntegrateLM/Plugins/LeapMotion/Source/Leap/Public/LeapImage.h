#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapImage.generated.h"


UCLASS(BlueprintType)
class LEAPMOTION_API ULeapImage : public UObject
{
	friend class PrivateLeapImage;

	GENERATED_UCLASS_BODY()
public:
	~ULeapImage();


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Texture", CompactNodeTitle = "", Keywords = "get texture"), Category = "Leap Image")
	class UTexture2D* Texture();
	

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distortion", CompactNodeTitle = "", Keywords = "distortion"), Category = "Leap Image")
	class UTexture2D* Distortion();


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distortion UE", CompactNodeTitle = "", Keywords = "distortion ue"), Category = "Leap Image")
	class UTexture2D* DistortionUE();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	int32 DistortionHeight;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	int32 DistortionWidth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	int32 Height;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	int32 Id;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	bool IsValid;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	float RayOffsetX;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	float RayOffsetY;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	float RayScaleX;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	float RayScaleY;


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "rectify", CompactNodeTitle = "", Keywords = "rectify"), Category = "Leap Image")
	FVector Rectify(FVector uv) const;


	UPROPERTY(EditAnywhere)
	int64 Timestamp;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	bool UseGammaCorrection;


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "warp", CompactNodeTitle = "", Keywords = "warp"), Category = "Leap Image")
	FVector Warp(FVector XY) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	int32 Width;


	void SetLeapImage(const class Leap::Image &LeapImage);

private:
	class PrivateLeapImage* Private = nullptr;

	UPROPERTY()
	UTexture2D* PImagePointer = nullptr;
	UPROPERTY()
	UTexture2D* PDistortionPointer = nullptr;
};