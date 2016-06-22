#pragma once

#include "AnimHand.h"
#include "AnimBody.generated.h"

* Animation Body object used to hold tracked animation state and provide
* convenience functions for re-basing and shifting the whole skeleton data.
*/
UCLASS(ClassGroup = "Animation Skeleton", meta = (BlueprintSpawnableComponent))
class LEAPMOTION_API UAnimBody : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	
	* Tracked state alpha. Vary the value to blend animation with tracked information.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Anim Body")
	float Alpha;


	UPROPERTY(BlueprintReadOnly, Category = "Anim Body")
	UAnimHand* Left;


	UPROPERTY(BlueprintReadOnly, Category = "Anim Body")
	UAnimHand* Right;


	UPROPERTY(BlueprintReadOnly, Category = "Anim Body")
	UAnimBone* Head;


	UFUNCTION(BlueprintCallable, Category = "Anim Body")
	bool Enabled();


	UFUNCTION(BlueprintCallable, Category = "Anim Body")
	void SetEnabled(bool Enable = true);


	UFUNCTION(BlueprintCallable, Category = "Anim Body")
	void TranslateBody(FVector Shift);


	UFUNCTION(BlueprintCallable, Category = "Anim Body")
	void ChangeBasis(FRotator PreBase, FRotator PostBase, bool AdjustVectors = true);
};