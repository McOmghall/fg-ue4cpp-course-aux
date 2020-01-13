// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "BTTask_GetWanderLocation.generated.h"

UCLASS(BlueprintType, Blueprintable)
class STATEMACHINEEXAMPLE_API UBTTask_GetWanderLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector MoveAroundPointOrigin;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float Radius = 200.0f;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
