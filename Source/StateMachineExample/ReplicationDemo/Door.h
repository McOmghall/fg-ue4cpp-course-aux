// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/SkeletalMeshActor.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimInstance.h"
#include "Door.generated.h"

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetNameStringByIndex((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

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

	UFUNCTION()
	void OnRep_IsOpen(bool bOldIsOpen);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "Door")
	void ServerSetIsOpen(bool bNewIsOpen);
	bool ServerSetIsOpen_Validate(bool bNewIsOpen) { return true; };
	void ServerSetIsOpen_Implementation(bool bNewIsOpen);


	UFUNCTION(BlueprintCallable, Client, Reliable, WithValidation, Category = "Door")
	void ClientTest();
	bool ClientTest_Validate() { return true; };
	void ClientTest_Implementation()
	{
		UE_LOG(LogTemp, Warning, TEXT("Client function called in %s"), *(GETENUMSTRING("ENetRole", GetLocalRole())));
	};

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, WithValidation, Category = "Door")
	void MulticastTest();
	bool MulticastTest_Validate() { return true; };
	void MulticastTest_Implementation()
	{
		UE_LOG(LogTemp, Warning, TEXT("NetMulticast function called in %s"), *(GETENUMSTRING("ENetRole", GetLocalRole())));
	};
};
