

#include "GearVR_QS.h"
#include "GearVR_QSGameMode.h"
#include "GearVR_QSHUD.h"
#include "GearVR_QSCharacter.h"

AGearVR_QSGameMode::AGearVR_QSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGearVR_QSHUD::StaticClass();
}
