
#pragma once

#include "VRReachSpec.h"
#include "VRRecastNavMesh.h"
#include "VRJumpPad.h"

#include "VRReachSpec_JumpPad.generated.h"

UCLASS(CustomConstructor)
class UNREALTOURNAMENT_API UVRReachSpec_JumpPad : public UVRReachSpec
{
	GENERATED_UCLASS_BODY()

	/** the jump pad Actor that needs to be touched to jump */
	UPROPERTY()
	TWeakObjectPtr<AVRJumpPad> JumpPad;

	UVRReachSpec_JumpPad(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	{
		PathColor = FLinearColor(0.0f, 0.0f, 1.0f);
	}

	virtual TWeakObjectPtr<AActor> GetSourceActor() const override
	{
		return JumpPad;
	}

	virtual int32 CostFor(int32 DefaultCost, const FVRPathLink& OwnerLink, APawn* Asker, const FNavAgentProperties& AgentProps, NavNodeRef StartPoly, const class AVRRecastNavMesh* NavMesh) override
	{
		if (!JumpPad.IsValid() || !JumpPad->IsEnabled())
		{
			// TODO: check for trigger to enable?
			return BLOCKED_PATH_COST;
		}
		else
		{
			int32 AdjustedCost = DefaultCost;
			// add extra cost if the boost goes through water which will slow us down
			if (OwnerLink.ReachFlags & R_SWIM)
			{
				AdjustedCost += FMath::TruncToInt((NavMesh->GetPolyCenter(OwnerLink.StartEdgePoly) - NavMesh->GetPolyCenter(OwnerLink.EndPoly)).Size()) / 2;
			}
			return AdjustedCost;
		}
	}

	virtual bool GetMovePoints(const FVRPathLink& OwnerLink, const FVector& StartLoc, APawn* Asker, const FNavAgentProperties& AgentProps, const struct FRoVReCacheItem& Target, const TArray<FRoVReCacheItem>& FullRoVRe, const class AVRRecastNavMesh* NavMesh, TArray<FComponentBasedPosition>& MovePoints) const
	{
		TArray<NavNodeRef> PolyRoVRe;
		NavMesh->FindPolyPath(StartLoc, AgentProps, FRoVReCacheItem(NavMesh->GetPolyCenter(OwnerLink.StartEdgePoly), OwnerLink.StartEdgePoly), PolyRoVRe, false);
		NavMesh->DoStringPulling(StartLoc, PolyRoVRe, AgentProps, MovePoints);
		if (JumpPad.IsValid())
		{
			MovePoints.Add(FComponentBasedPosition(JumpPad->GetRootComponent(), JumpPad->GetActorLocation()));
		}
		MovePoints.Add(FComponentBasedPosition(Target.GetLocation(Asker)));
		return true;
	}
};