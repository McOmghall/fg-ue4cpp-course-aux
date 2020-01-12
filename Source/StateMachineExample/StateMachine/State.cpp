// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"

void UState::OnStateEntered_Implementation(AActor * Owner)
{
}

void UState::OnStateTicking_Implementation(AActor * Owner)
{
}

void UState::OnStateExited_Implementation(AActor * Owner)
{
}

UClass* UState::TransitionState(FName Event)
{
	if (TransitionMap.Contains(Event))
	{
		return TransitionMap.Find(Event)->Get();
	}
	return nullptr;
}
