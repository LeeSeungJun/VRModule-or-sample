
#pragma once 
#include "GameFramework/HUD.h"
#include "GearVR_QSHUD.generated.h"

UCLASS()
class AGearVR_QSHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGearVR_QSHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class VRexture2D* CrosshairTex;

};

