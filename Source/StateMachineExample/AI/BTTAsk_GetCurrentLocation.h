// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BTTAsk_GetCurrentLocation.generated.h"

UCLASS(BlueprintType, Blueprintable)
class STATEMACHINEEXAMPLE_API UBTTAsk_GetCurrentLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
