// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckPlayerVisible.generated.h"

/**
 * 
 */
UCLASS()
class STATEMACHINEEXAMPLE_API UBTService_CheckPlayerVisible : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, Category = Blackboard)
    float AngleTolerance = 90.0f;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
