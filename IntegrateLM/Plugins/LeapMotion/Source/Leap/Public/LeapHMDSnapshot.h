#pragma once

#include "LeapMotionPublicPCH.h"


struct LeapHMDSnapshot
{
public:
	int64 Timestamp;
	FVector Position;
	FQuat Orientation;

	LeapHMDSnapshot() {};
	FORCEINLINE LeapHMDSnapshot(int64 InTimeStamp, const FVector& InPosition, const FQuat& InOrientation);

	FORCEINLINE LeapHMDSnapshot Difference(LeapHMDSnapshot& Other, float Tween);

	FORCEINLINE FTransform Transform();

	FORCEINLINE LeapHMDSnapshot operator*(float Mult);
	FORCEINLINE void operator*=(float Mult);
};

LeapHMDSnapshot::LeapHMDSnapshot(int64 InTimeStamp, const FVector& InPosition, const FQuat& InOrientation)
{
	Timestamp = InTimeStamp;
	Position = InPosition;
	Orientation = InOrientation;
}
LeapHMDSnapshot LeapHMDSnapshot::Difference(LeapHMDSnapshot& Other, float Tween)
{
	LeapHMDSnapshot Result;
	Result.Timestamp = Timestamp - Other.Timestamp;
	Other.Orientation = FQuat::Slerp(Orientation, Other.Orientation, Tween);

	FTransform DeltaTransform = Other.Transform().GetRelativeTransform(Transform());

	Result.Orientation = DeltaTransform.GetRotation();
	Result.Position = DeltaTransform.GetTranslation();
	return Result;
}

FTransform LeapHMDSnapshot::Transform()
{
	return FTransform(Orientation, Position, FVector(1.f));
}


FORCEINLINE LeapHMDSnapshot LeapHMDSnapshot::operator*(float Mult)
{
	return LeapHMDSnapshot(Timestamp, Position * Mult, Orientation * Mult);
}

FORCEINLINE void LeapHMDSnapshot::operator*=(float Mult)
{
	this->Position *= Mult;
	this->Orientation *= Mult;
}