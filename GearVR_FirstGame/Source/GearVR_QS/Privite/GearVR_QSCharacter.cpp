

#include "GearVR_QS.h"
#include "GearVR_QSCharacter.h"
#include "GearVR_QSProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InpVRSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AGearVR_QSCharacter

AGearVR_QSCharacter::AGearVR_QSCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for inpVR
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->AttachTo(Mesh1P, TEXT("GripPoint"), EAttachLocation::SnapToTargetIncludingScale, true);


	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// InpVR

void AGearVR_QSCharacter::SetupPlayerInpVRComponent(class UInpVRComponent* InpVRComponent)
{
	// set up gameplay key bindings
	check(InpVRComponent);

	InpVRComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InpVRComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	//InpVRComponent->BindTouch(EInpVREvent::IE_Pressed, this, &AGearVR_QSCharacter::TouchStarted);
	if( EnableTouchscreenMovement(InpVRComponent) == false )
	{
		InpVRComponent->BindAction("Fire", IE_Pressed, this, &AGearVR_QSCharacter::OnFire);
	}
	
	InpVRComponent->BindAxis("MoveForward", this, &AGearVR_QSCharacter::MoveForward);
	InpVRComponent->BindAxis("MoveRight", this, &AGearVR_QSCharacter::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolVRe delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InpVRComponent->BindAxis("Turn", this, &APawn::AddControllerYawInpVR);
	InpVRComponent->BindAxis("TurnRate", this, &AGearVR_QSCharacter::TurnAtRate);
	InpVRComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInpVR);
	InpVRComponent->BindAxis("LookUpRate", this, &AGearVR_QSCharacter::LookUpAtRate);
}

void AGearVR_QSCharacter::OnFire()
{ 
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AGearVR_QSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if(FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if(AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

}

void AGearVR_QSCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if( TouchItem.bIsPressed == true )
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AGearVR_QSCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if( ( FingerIndex == TouchItem.FingerIndex ) && (TouchItem.bMoved == false) )
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

void AGearVR_QSCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if ((TouchItem.bIsPressed == true) && ( TouchItem.FingerIndex==FingerIndex))
	{
		if (TouchItem.bIsPressed)
		{
			if (GetWorld() != nullptr)
			{
				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
				if (ViewportClient != nullptr)
				{
					FVector MoveDelta = Location - TouchItem.Location;
					FVector2D ScreenSize;
					ViewportClient->GetViewportSize(ScreenSize);
					FVector2D ScaledDelta = FVector2D( MoveDelta.X, MoveDelta.Y) / ScreenSize;									
					if (ScaledDelta.X != 0.0f)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.X * BaseTurnRate;
						AddControllerYawInpVR(Value);
					}
					if (ScaledDelta.Y != 0.0f)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.Y* BaseTurnRate;
						AddControllerPitchInpVR(Value);
					}
					TouchItem.Location = Location;
				}
				TouchItem.Location = Location;
			}
		}
	}
}

void AGearVR_QSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInpVR(GetActorForwardVector(), Value);
	}
}

void AGearVR_QSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInpVR(GetActorRightVector(), Value);
	}
}

void AGearVR_QSCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInpVR(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGearVR_QSCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInpVR(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AGearVR_QSCharacter::EnableTouchscreenMovement(class UInpVRComponent* InpVRComponent)
{
	bool bResult = false;
	if(FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInpVRSettings>()->bUseMouseForTouch )
	{
		bResult = true;
		InpVRComponent->BindTouch(EInpVREvent::IE_Pressed, this, &AGearVR_QSCharacter::BeginTouch);
		InpVRComponent->BindTouch(EInpVREvent::IE_Released, this, &AGearVR_QSCharacter::EndTouch);
		InpVRComponent->BindTouch(EInpVREvent::IE_Repeat, this, &AGearVR_QSCharacter::TouchUpdate);
	}
	return bResult;
}
