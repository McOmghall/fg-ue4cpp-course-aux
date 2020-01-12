// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates\SubclassOf.h"
#include "UObject/NoExportTypes.h"
#include "State.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Category = "State Machine")
class STATEMACHINEEXAMPLE_API UState : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "States")
	TMap<FName, TSubclassOf<UState>> TransitionMap;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "States")
	void OnStateEntered(AActor* Owner);
	void OnStateEntered_Implementation(AActor* Owner);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "States")
	void OnStateTicking(AActor* Owner);
	void OnStateTicking_Implementation(AActor* Owner);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "States")
	void OnStateExited(AActor* Owner);
	void OnStateExited_Implementation(AActor* Owner);

	UFUNCTION(BlueprintCallable, Category = "States")
	UClass* TransitionState(FName Event);
};
