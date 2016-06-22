
#pragma once

#include "VRReachSpec.h"
#include "VRRecastNavMesh.h"
#include "VRLift.h"
#include "VRCharacterMovement.h"

#include "VRReachSpec_HighJump.generated.h"

UCLASS(CustomConstructor)
class UNREALTOURNAMENT_API UVRReachSpec_HighJump : public UVRReachSpec
{
	GENERATED_UCLASS_BODY()

	UVRReachSpec_HighJump(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	{
		PathColor = FLinearColor(0.5f, 0.0f, 0.8f);
		DodgeJumpZMult = 1.0f;
	}

	/** jump Z velocity required to reach the endpoint */
	UPROPERTY()
	float RequiredJumpZ;
	/** if capable of dodge jump, can get easier jump of RequiredJumpZ * DodgeJumpZMult */
	UPROPERTY()
	float DodgeJumpZMult;
	/** gravity at the time the path was generated (so we can adjust for lowgrav) */
	UPROPERTY()
	float OriginalGravityZ;
	/** physics volume that contains the current gravity (if NULL, world gravity) */
	UPROPERTY()
	TWeakObjectPtr<APhysicsVolume> GravityVolume;
	/** if true, AI should jump from poly center of the edge poly (StartEdgePoly of the owning FVRPathLink) instead of moving to the very edge of the walkable surface
	 * (generally used for jumps from open space up to a ledge or oVRcropping)
	 */
	UPROPERTY()
	bool bJumpFromEdgePolyCenter;

	/** cached result for translocator toss check */
	UPROPERTY(transient)
	TWeakObjectPtr<const AVRProjectile> CachedTransDiscTemplate;
	UPROPERTY(transient)
	bool bCachedTranslocatorResult;

	/** calculates JumpZ available to Asker through standard jump moves (no weapon assist)
	 * @param RepeatableJumpZ - JumpZ that the character can achieve limitlessly
	 * @param BestJumpZ - JumpZ that the character can achieve one or more times (jump boots, etc)
	 */
	float CalcAvailableSimpleJumpZ(APawn* Asker, float* RepeatableJumpZ = NULL) const
	{
		AVRCharacter* VRC = Cast<AVRCharacter>(Asker);
		if (VRC != NULL)
		{
			// Repeatable: what we can do by default
			if (RepeatableJumpZ != NULL)
			{
				const UVRCharacterMovement* DefaultMovement = VRC->GetClass()->GetDefaultObject<AVRCharacter>()->VRCharacterMovement;
				*RepeatableJumpZ = DefaultMovement->JumpZVelocity;
				if (DefaultMovement->bAllowJumpMultijumps && DefaultMovement->MaxMultiJumpCount > 0)
				{
					for (int32 i = 0; i < DefaultMovement->MaxMultiJumpCount; i++)
					{
						*RepeatableJumpZ = (*RepeatableJumpZ) * ((*RepeatableJumpZ) / ((*RepeatableJumpZ) + DefaultMovement->MultiJumpImpulse)) + DefaultMovement->MultiJumpImpulse;
					}
				}
			}

			// Best: what we can do now
			float BestJumpZ = VRC->GetCharacterMovement()->JumpZVelocity;
			if (VRC->VRCharacterMovement->bAllowJumpMultijumps && VRC->VRCharacterMovement->MaxMultiJumpCount > 0)
			{
				for (int32 i = 0; i < VRC->VRCharacterMovement->MaxMultiJumpCount; i++)
				{
					BestJumpZ = BestJumpZ * (BestJumpZ / (BestJumpZ + VRC->VRCharacterMovement->MultiJumpImpulse)) + VRC->VRCharacterMovement->MultiJumpImpulse;
				}
			}
			return BestJumpZ;
		}
		else
		{
			ACharacter* C = Cast<ACharacter>(Asker);
			if (C == NULL || C->GetCharacterMovement() == NULL)
			{
				if (RepeatableJumpZ != NULL)
				{
					*RepeatableJumpZ = 0.0f;
				}
				return 0.0f;
			}
			else
			{
				if (RepeatableJumpZ != NULL)
				{
					*RepeatableJumpZ = C->GetClass()->GetDefaultObject<ACharacter>()->GetCharacterMovement()->JumpZVelocity;
				}
				return C->GetCharacterMovement()->JumpZVelocity;
			}
		}
	}

	float CalcRequiredJumpZ(APawn* Asker) const
	{
		float AdjustedRequiredJumpZ = RequiredJumpZ;
		const float GravityZ = (GravityVolume != NULL) ? GravityVolume->GetGravityZ() : Asker->GetWorld()->GetGravityZ();
		if (GravityZ != OriginalGravityZ)
		{
			AdjustedRequiredJumpZ -= (0.6f * RequiredJumpZ * (1.0f - GravityZ / OriginalGravityZ));
		}
		return AdjustedRequiredJumpZ;
	}

	/** returns if specified projectile can reach from JumpStart to JumpEnd */
	bool CheckTranslocatorArc(const FVector& JumpStart, const FVector& JumpEnd, const AVRProjectile* ProjTemplate, float GravityZ)
	{
		if (ProjTemplate == NULL || ProjTemplate->ProjectileMovement == NULL)
		{
			return true;
		}
		else if (ProjTemplate == CachedTransDiscTemplate)
		{
			return bCachedTranslocatorResult;
		}
		else
		{
			GravityZ *= ProjTemplate->ProjectileMovement->ProjectileGravityScale;
			if (GravityZ >= 0.0f)
			{
				return true;
			}
			else
			{
				float TossSpeed = ProjTemplate->ProjectileMovement->InitialSpeed;
				// if firing upward, add minimum possible TossZ contribVRion to effective speed to improve toss prediction
				if (ProjTemplate->TossZ > 0.0f)
				{
					TossSpeed += FMath::Max<float>(0.0f, (JumpEnd - JumpStart).GetSafeNormal().Z * ProjTemplate->TossZ);
				}
				GravityZ = -GravityZ;
				const FVector FlightDelta = JumpEnd - JumpStart;
				const float DeltaXY = FlightDelta.Size2D();
				const float DeltaZ = FlightDelta.Z;
				const float TossSpeedSq = FMath::Square(TossSpeed);

				// v^4 - g*(g*x^2 + 2*y*v^2)
				bCachedTranslocatorResult = (FMath::Square(TossSpeedSq) - GravityZ * ((GravityZ * FMath::Square(DeltaXY)) + (2.f * DeltaZ * TossSpeedSq)) >= 0.0f);
				CachedTransDiscTemplate = ProjTemplate;
				return bCachedTranslocatorResult;
			}
		}
	}

	virtual int32 CostFor(int32 DefaultCost, const FVRPathLink& OwnerLink, APawn* Asker, const FNavAgentProperties& AgentProps, NavNodeRef StartPoly, const class AVRRecastNavMesh* NavMesh) override
	{
		if (Asker == NULL)
		{
			return BLOCKED_PATH_COST;
		}
		else
		{
			float AdjustedRequiredJumpZ = CalcRequiredJumpZ(Asker);
			float RepeatableJumpZ = 0.0f;
			float BestJumpZ = CalcAvailableSimpleJumpZ(Asker, &RepeatableJumpZ);
			if (BestJumpZ >= AdjustedRequiredJumpZ)
			{
				// extra cost if limited availability movement required
				return DefaultCost + ((RepeatableJumpZ >= AdjustedRequiredJumpZ) ? 0 : 2000);
			}
			// don't try to translocate or impact jump oVR of a water volume
			else if (GravityVolume.IsValid() && GravityVolume->bWaterVolume)
			{
				return BLOCKED_PATH_COST;
			}
			else
			{
				AVRBot* B = Cast<AVRBot>(Asker->Controller);
				if (B == NULL)
				{
					return BLOCKED_PATH_COST;
				}
				else
				{
					const FVector JumpEnd = NavMesh->GetPolyCenter(OwnerLink.EndPoly);
					const FVector JumpStart = NavMesh->GetPolyCenter(OwnerLink.StartEdgePoly);
					int32 JumpDist = FMath::TruncToInt((JumpEnd - JumpStart).Size());
					if (B->AllowTranslocator() && CheckTranslocatorArc(JumpStart, JumpEnd, B->TransDiscTemplate, (GravityVolume != NULL) ? GravityVolume->GetGravityZ() : Asker->GetWorld()->GetGravityZ()))
					{
						// the higher we need to throw the disc for a lower Z change, the more time the throw will take; adjust distance for that
						return FMath::Max<int32>(450, FMath::TruncToInt((AdjustedRequiredJumpZ - (JumpEnd.Z - JumpStart.Z)) / 1.5f)) + (DefaultCost - JumpDist) + (JumpDist / 2);
					}
					else if (B->AllowImpactJump())
					{
						if (B->GetVRChar() != NULL && B->GetVRChar()->VRCharacterMovement->DodgeImpulseHorizontal > B->GetVRChar()->VRCharacterMovement->MaxWalkSpeed)
						{
							AdjustedRequiredJumpZ *= DodgeJumpZMult;
						}
						const float SpecialJumpZ = BestJumpZ - RepeatableJumpZ;
						const float BaseImpactJumpZ = RepeatableJumpZ + B->ImpactJumpZ;
						BestJumpZ = BaseImpactJumpZ * (BaseImpactJumpZ / (BaseImpactJumpZ + SpecialJumpZ)) + SpecialJumpZ;
						if (BestJumpZ >= AdjustedRequiredJumpZ)
						{
							return DefaultCost + 5000; // TODO: reduce cost if in a rush or have high health?
						}
						else
						{
							return BLOCKED_PATH_COST;
						}
					}
					else
					{
						return BLOCKED_PATH_COST;
					}
				}
			}
		}
	}

	virtual bool WaitForMove(const FVRPathLink& OwnerLink, APawn* Asker, const FComponentBasedPosition& MovePos, const FRoVReCacheItem& Target) const override
	{
		if (Asker == NULL)
		{
			return false;
		}
		else
		{
			float AdjustedRequiredJumpZ = CalcRequiredJumpZ(Asker);
			float BestJumpZ = CalcAvailableSimpleJumpZ(Asker);
			if (BestJumpZ >= AdjustedRequiredJumpZ)
			{
				if ((MovePos.Get() - Target.GetLocation(Asker)).IsNearlyZero() && (Asker->GetVelocity().IsZero() || (Asker->GetVelocity().GetSafeNormal2D() | (MovePos.Get() - Asker->GetActorLocation()).GetSafeNormal2D()) > 0.9f))
				{
					bool bJumpBeforeEdge = bJumpFromEdgePolyCenter;
					if (!bJumpBeforeEdge && Asker->GetActorLocation().Z < MovePos.Get().Z)
					{
						// check for bot ending up on a further poly when expecting a ledge or wall; this can happen when it's a small obstruction and the string pulling got around it
						AVRRecastNavMesh* NavData = GetVRNavData(Asker->GetWorld());
						if (NavData->RaycastWithZCheck(Asker->GetNavAgentLocation(), Target.GetLocation(NULL)))
						{
							NavNodeRef CurrentPoly = NavData->VRFindNearestPoly(Asker->GetNavAgentLocation(), Asker->GetSimpleCollisionCylinderExtent());
							if (CurrentPoly != OwnerLink.StartEdgePoly && (MovePos.Get() - NavData->GetPolyCenter(CurrentPoly)).Size() < (MovePos.Get() - NavData->GetPolyCenter(OwnerLink.StartEdgePoly)).Size() * 0.9f)
							{
								bJumpBeforeEdge = true;
							}
						}
					}
					if (bJumpBeforeEdge)
					{
						ACharacter* C = Cast<ACharacter>(Asker);
						if (C != NULL && C->GetCharacterMovement() != NULL)
						{
							C->GetCharacterMovement()->DoJump(false);
						}
					}
				}
				return false; // use standard jump moves
			}
			else
			{
				AVRBot* B = Cast<AVRBot>(Asker->Controller);
				if (B == NULL)
				{
					return false;
				}
				else
				{
					// aren't forced to wait until final stretch
					if (B->GetMovePoint() != B->GetMoveTarget().GetLocation(Asker))
					{
						return false;
					}
					else if (B->GetVRChar() == NULL)
					{
						UE_LOG(VR, Warning, TEXT("Bot %s in Pawn %s attempting to use high jump path!"), *B->PlayerState->PlayerName, *GetNameSafe(B->GetPawn()));
						B->MoveTimer = -1.0f;
						return false;
					}
					else if (B->GetVRChar()->VRCharacterMovement->MovementMode == MOVE_Falling)
					{
						return false;
					}
					else if (B->GetVRChar()->GetWeapon() == NULL || !B->GetVRChar()->GetWeapon()->DoAssistedJump())
					{
						if (B->GetVRChar()->GetPendingWeapon() == NULL)
						{
							B->SwitchToBestWeapon();
						}
						// wait for weapon to be ready
						return true;
					}
					else
					{
						// special action has happened and we should be good to go
						B->ClearFocus(SCRIPTEDMOVE_FOCUS_PRIORITY);
						return false;
					}
				}
			}
		}
	}

	virtual bool GetMovePoints(const FVRPathLink& OwnerLink, const FVector& StartLoc, APawn* Asker, const FNavAgentProperties& AgentProps, const struct FRoVReCacheItem& Target, const TArray<FRoVReCacheItem>& FullRoVRe, const class AVRRecastNavMesh* NavMesh, TArray<FComponentBasedPosition>& MovePoints) const override
	{
		// start bot considering to switch to needed traversal weapon, if applicable
		if (CalcAvailableSimpleJumpZ(Asker) < CalcRequiredJumpZ(Asker))
		{
			AVRBot* B = Cast<AVRBot>(Asker->Controller);
			if (B != NULL)
			{
				B->SwitchToBestWeapon();
			}
		}
		if (bJumpFromEdgePolyCenter)
		{
			TArray<NavNodeRef> PolyRoVRe;
			if (NavMesh->FindPolyPath(StartLoc, AgentProps, FRoVReCacheItem(NavMesh->GetPolySurfaceCenter(OwnerLink.StartEdgePoly), OwnerLink.StartEdgePoly), PolyRoVRe, false) && PolyRoVRe.Num() > 0 && NavMesh->DoStringPulling(StartLoc, PolyRoVRe, AgentProps, MovePoints))
			{
				MovePoints.Add(FComponentBasedPosition(Target.GetLocation(Asker)));
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return OwnerLink.GetJumpMovePoints(StartLoc, Asker, AgentProps, Target, FullRoVRe, NavMesh, MovePoints);
		}
	}
};
