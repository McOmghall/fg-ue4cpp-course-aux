// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsCloseEnough.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Kismet/GameplayStatics.h"

bool UBTDecorator_IsCloseEnough::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(OwnerComp.GetWorld(), 0);
	AActor* PlayerPawn = PlayerController ? PlayerController->GetPawn() : nullptr;
	AActor* ControlledPawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;

	if (PlayerPawn == nullptr || ControlledPawn == nullptr)
	{
		return false;
	}

	// Check if it's close
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector OwnLocation = ControlledPawn->GetActorLocation();
	float DistanceToPlayer = (PlayerLocation - OwnLocation).Size();

	return DistanceToPlayer <= Threshold;
}