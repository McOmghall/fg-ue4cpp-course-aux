// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineComponent.h"

// Sets default values
UStateMachineComponent::UStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = bCanTickEnable;
}

// Called when the game starts or when spawned
void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	UState* FirstState = NewObject<UState>(this, InitialState);
	SetState(FirstState);
}

// Called every frame
void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* LocalOwner = GetOwnerSafe();
	if (LocalOwner != nullptr && HasCurrentState())
	{
		CurrentState->OnStateTicking(LocalOwner);
	}
}

UState * UStateMachineComponent::SetState(UState * NewState)
{
	// If this component's owner is marked for destruction or non-existent, probably this component is too (or unnecesary) so skip
	if (AActor* LocalOwner = GetOwnerSafe())
	{
		// Just run the callbacks on the states and swap for the new state
		if (HasCurrentState())
		{
			CurrentState->OnStateExited(LocalOwner);
		}

		CurrentState = NewState;
		CurrentState->OnStateEntered(LocalOwner);

		return CurrentState;
	}
	return nullptr;
}

void UStateMachineComponent::ReceiveEvent(FName Event)
{
	if (!HasCurrentState())
	{
		return;
	}
	
	if (TSubclassOf<UState> Transition = CurrentState->TransitionState(Event))
	{
		SetState(NewObject<UState>(this, Transition));
	}
}

AActor * UStateMachineComponent::GetOwnerSafe()
{
	AActor* LocalOwner = GetOwner();
	// Introduce mistake !LocalOwner->IsPendingKill()
	if (LocalOwner == nullptr || !LocalOwner->IsValidLowLevel() || LocalOwner->IsPendingKill())
	{
		return nullptr;
	}
	return LocalOwner;
}

inline bool UStateMachineComponent::HasCurrentState()
{
	return CurrentState != nullptr && CurrentState->IsValidLowLevel();
}

