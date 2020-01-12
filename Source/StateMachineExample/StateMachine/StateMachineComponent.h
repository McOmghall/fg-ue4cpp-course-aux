// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "State.h"
#include "StateMachineComponent.generated.h"

UCLASS(BlueprintType, Blueprintable, Category = "State Machine")
class STATEMACHINEEXAMPLE_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UStateMachineComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Performance")
	bool bCanTickEnable = true;

	/**
	 * The initial state
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "States")
	TSubclassOf<UState> InitialState;

	/**
	 * Keep track of the current state of the execution
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
	UState* CurrentState = nullptr;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "States")
	UState* SetState(UState* NewState);

	UFUNCTION(BlueprintCallable, Category = "States")
	void ReceiveEvent(FName Event);

private:
	inline AActor* GetOwnerSafe();
	inline bool HasCurrentState();
};
