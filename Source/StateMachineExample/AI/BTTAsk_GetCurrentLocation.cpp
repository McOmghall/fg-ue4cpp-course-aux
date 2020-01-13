// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTAsk_GetCurrentLocation.h"



EBTNodeResult::Type UBTTAsk_GetCurrentLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AActor* Owner = Blackboard->GetOwner();
	if (Owner == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	return Blackboard->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.SelectedKeyName, Owner->GetActorLocation()) ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}