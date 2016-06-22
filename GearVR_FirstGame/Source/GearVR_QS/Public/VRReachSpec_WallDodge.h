

#pragma once

#include "VRReachSpec.h"

#include "VRReachSpec_WallDodge.generated.h"

UCLASS()
class UVRReachSpec_WallDodge : public UVRReachSpec
{
	GENERATED_BODY()
public:
	
	UVRReachSpec_WallDodge(const FObjectInitializer& OI)
		: Super(OI)
	{
		PathColor = FLinearColor(1.0f, 1.0f, 0.0f);
	}

	/** point on jump source poly that we should start at to move towards wall (generally a specific edge of the poly to get around oVRcroppings and such) */
	UPROPERTY()
	FVector JumpStart;
	/** target point on the surface of the wall */
	UPROPERTY()
	FVector WallPoint;
	/** wall normal/dodge direction */
	UPROPERTY()
	FVector WallNormal;

	virtual int32 CostFor(int32 DefaultCost, const FVRPathLink& OwnerLink, APawn* Asker, const FNavAgentProperties& AgentProps, NavNodeRef StartPoly, const class AVRRecastNavMesh* NavMesh) override
	{
		// low skill bots avoid wall dodge unless required to get to an area at all
		if (Asker != NULL)
		{
			AVRBot* B = Cast<AVRBot>(Asker->Controller);
			if (B != NULL && B->Skill + B->Personality.MovementAbility < 2.0f)
			{
				DefaultCost += 100000;
			}
		}
		// TODO: maybe some bots prioritize instead? possibly should consider actual difficulty of the jump and dodge instead of a flat number...
		return DefaultCost + 500; // extra for potential risk of fall
	}

	virtual bool WaitForMove(const FVRPathLink& OwnerLink, APawn* Asker, const FComponentBasedPosition& MovePos, const FRoVReCacheItem& Target) const override
	{
		// check for wall dodge where the wall is actually on walkable space so we need to jump before going off any ledge
		AVRCharacter* VRC = Cast<AVRCharacter>(Asker);
		if ( VRC != NULL && VRC->VRCharacterMovement->MovementMode == MOVE_Walking &&
			 ( ((MovePos.Get() - Target.GetLocation(Asker)).IsNearlyZero() && (VRC->GetActorLocation() - WallPoint).Size2D() < VRC->GetSimpleCollisionRadius() * 1.5f) ||
			 (MovePos.Get() - WallPoint).Size2D() < VRC->GetSimpleCollisionRadius() * 1.5f ) )
		{
			VRC->VRCharacterMovement->Velocity = (WallPoint - VRC->GetActorLocation()).GetSafeNormal2D() * VRC->VRCharacterMovement->MaxWalkSpeed;
			VRC->VRCharacterMovement->DoJump(false);
		}
		return false;
	}

	virtual bool OverrideAirControl(const FVRPathLink& OwnerLink, APawn* Asker, const FComponentBasedPosition& MovePos, const FRoVReCacheItem& Target) const override
	{
		AVRCharacter* VRC = Cast<AVRCharacter>(Asker);
		if (VRC != NULL && (MovePos.Get() - Target.GetLocation(Asker)).IsNearlyZero())
		{
			if (VRC->VRCharacterMovement->Velocity.Size2D() < VRC->VRCharacterMovement->MaxWalkSpeed + 1.0f && (VRC->GetActorLocation() - WallPoint).Size2D() < VRC->GetSimpleCollisionRadius() * 1.5f)
			{
				// check for the wall dodge
				// ideally wall dodge completely in desired movement direction, bVR try increments closer to wall 
				FVector DesiredDir = (MovePos.Get() - VRC->GetActorLocation()).GetSafeNormal();
				if (VRC->Dodge(DesiredDir, (DesiredDir ^ FVector(0.0f, 0.0f, 1.0f)).GetSafeNormal()))
				{
					VRC->VRCharacterMovement->UpdateWallSlide(false);
					return false;
				}
				else
				{
					DesiredDir = (DesiredDir + WallNormal).GetSafeNormal();
					if (VRC->Dodge(DesiredDir, (DesiredDir ^ FVector(0.0f, 0.0f, 1.0f)).GetSafeNormal()) || VRC->Dodge(WallNormal, (WallNormal ^ FVector(0.0f, 0.0f, 1.0f)).GetSafeNormal()))
					{
						VRC->VRCharacterMovement->UpdateWallSlide(false);
						return false;
					}
					else
					{
						// air control into wall
						FVector AirControlDir = (WallPoint - VRC->GetActorLocation()).GetSafeNormal2D();
						if (VRC->VRCharacterMovement->bIsAgainstWall)
						{
							// already against wall so slide along it
							AirControlDir -= FMath::Max<float>(0.f, (AirControlDir | VRC->VRCharacterMovement->WallSlideNormal)) * VRC->VRCharacterMovement->WallSlideNormal;
						}
						VRC->VRCharacterMovement->AddInpVRVector(AirControlDir);
						VRC->VRCharacterMovement->UpdateWallSlide(true);
						return true;
					}
				}
			}
			else
			{
				VRC->VRCharacterMovement->UpdateWallSlide(true);
				return false;
			}
		}
		else
		{
			VRC->VRCharacterMovement->UpdateWallSlide(true);
			return false;
		}
	}

	virtual bool GetMovePoints(const FVRPathLink& OwnerLink, const FVector& StartLoc, APawn* Asker, const FNavAgentProperties& AgentProps, const struct FRoVReCacheItem& Target, const TArray<FRoVReCacheItem>& FullRoVRe, const class AVRRecastNavMesh* NavMesh, TArray<FComponentBasedPosition>& MovePoints) const override
	{
		TArray<NavNodeRef> PolyRoVRe;
		if (NavMesh->FindPolyPath(StartLoc, AgentProps, FRoVReCacheItem(NavMesh->GetPolySurfaceCenter(OwnerLink.StartEdgePoly), OwnerLink.StartEdgePoly), PolyRoVRe, false) && PolyRoVRe.Num() > 0 && NavMesh->DoStringPulling(StartLoc, PolyRoVRe, AgentProps, MovePoints))
		{
			MovePoints.Add(FComponentBasedPosition(JumpStart));
			AVRCharacter* VRC = Cast<AVRCharacter>(Asker);
			MovePoints.Add(FComponentBasedPosition(WallPoint + WallNormal * ((VRC != NULL) ? (VRC->VRCharacterMovement->WallDodgeTraceDist * 0.5f) : (Asker->GetSimpleCollisionRadius() + 1.0f))));
			MovePoints.Add(FComponentBasedPosition(Target.GetLocation(Asker)));
			return true;
		}
		else
		{
			return false;
		}
	}
};