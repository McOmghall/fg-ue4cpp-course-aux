// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/SkeletalMeshActor.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimInstance.h"
#include "Door.generated.h"

UCLASS()
class STATEMACHINEEXAMPLE_API ADoor : public ASkeletalMeshActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	UAnimSequence* AnimationOnOpenClose = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_IsOpen, Category = "Door")
	bool bIsOpen = false;

	ADoor();
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Door")
	void SetIsOpen(bool bNewIsOpen);

	UFUNCTION()
	void OnRep_IsOpen(bool bOldIsOpen);
};
