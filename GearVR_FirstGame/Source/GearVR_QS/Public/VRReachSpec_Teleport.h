

#pragma once

#include "VRReachSpec.h"
#include "VRRecastNavMesh.h"

#include "VRReachSpec_Teleport.generated.h"

UCLASS(CustomConstructor)
class UNREALTOURNAMENT_API UVRReachSpec_Teleport : public UVRReachSpec
{
	GENERATED_UCLASS_BODY()

	/** the teleporter Actor that needs to be touched to teleport */
	UPROPERTY()
	TWeakObjectPtr<AActor> Teleporter;

	UVRReachSpec_Teleport(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	{
		PathColor = FLinearColor(0.0f, 0.0f, 1.0f);
	}

	virtual TWeakObjectPtr<AActor> GetSourceActor() const override
	{
		return Teleporter;
	}

	virtual int32 CostFor(int32 DefaultCost, const FVRPathLink& OwnerLink, APawn* Asker, const FNavAgentProperties& AgentProps, NavNodeRef StartPoly, const class AVRRecastNavMesh* NavMesh) override
	{
		// TODO: check if teleporter is active?
		return Teleporter.IsValid() ? DefaultCost : BLOCKED_PATH_COST;
	}

	virtual bool GetMovePoints(const FVRPathLink& OwnerLink, const FVector& StartLoc, APawn* Asker, const FNavAgentProperties& AgentProps, const struct FRoVReCacheItem& Target, const TArray<FRoVReCacheItem>& FullRoVRe, const class AVRRecastNavMesh* NavMesh, TArray<FComponentBasedPosition>& MovePoints) const
	{
		TArray<NavNodeRef> PolyRoVRe;
		NavMesh->FindPolyPath(StartLoc, AgentProps, FRoVReCacheItem(NavMesh->GetPolyCenter(OwnerLink.StartEdgePoly), OwnerLink.StartEdgePoly), PolyRoVRe, false);
		NavMesh->DoStringPulling(StartLoc, PolyRoVRe, AgentProps, MovePoints);
		if (Teleporter.IsValid())
		{
			MovePoints.Add(FComponentBasedPosition(Teleporter->GetRootComponent(), Teleporter->GetActorLocation()));
		}
		return true;
	}
};