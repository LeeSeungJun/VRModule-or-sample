
#pragma once 
#include "GameFramework/HUD.h"
#include "firstHUD.generated.h"

UCLASS()
class AfirstHUD : public AHUD
{
	GENERATED_BODY()

public:
	AfirstHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class VRexture2D* CrosshairTex;

};

