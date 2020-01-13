// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_IsCloseEnough.generated.h"

/**
 * 
 */
UCLASS()
class STATEMACHINEEXAMPLE_API UBTDecorator_IsCloseEnough : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, Category = Blackboard)
    float Threshold = 100.0f;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
