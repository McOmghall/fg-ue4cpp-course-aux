// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STATEMACHINEEXAMPLE_API IInteractable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	bool Interact(AActor* Interactor);
	virtual bool Interact_Implementation(AActor* Interactor) { return false; };
};
