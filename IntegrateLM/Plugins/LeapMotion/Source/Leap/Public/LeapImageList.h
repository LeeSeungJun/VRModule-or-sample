#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapImageList.generated.h"


UCLASS(BlueprintType)
class LEAPMOTION_API ULeapImageList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapImageList();
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image List")
	bool IsEmpty;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image List")
	int32 Count;
	

	* Access a list member by its position in the list.
	*
	* @param	Index	The zero-based list position index.
	* @return	The Image object at the specified index.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "getIndex", CompactNodeTitle = "", Keywords = "get index"), Category = "Leap Image List")
	class ULeapImage* GetIndex(int32 Index);

	ULeapImage* operator[](int Index);

	void SetLeapImageList(const class Leap::ImageList &LeapImageList);

private:
	class PrivateLeapImageList* Private;

	UPROPERTY()
	ULeapImage* PIndexImage1 = nullptr;
	UPROPERTY()
	ULeapImage* PIndexImage2 = nullptr;
};