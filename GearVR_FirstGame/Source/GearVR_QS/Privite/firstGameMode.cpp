

#include "first.h"
#include "firstGameMode.h"
#include "firstHUD.h"
#include "firstCharacter.h"

AfirstGameMode::AfirstGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AfirstHUD::StaticClass();
}
