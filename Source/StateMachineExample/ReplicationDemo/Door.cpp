// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"


ADoor::ADoor()
{
	bReplicates = true;
	GetSkeletalMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetSkeletalMeshComponent()->SetCollisionProfileName("NoCollision");
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this]
	{
		UE_LOG(LogTemp, Warning, TEXT("Client function BEGINPLAY call in %s"), *(GETENUMSTRING("ENetRole", GetLocalRole())));
		ClientTest();
		UE_LOG(LogTemp, Warning, TEXT("NetMulticast function BEGINPLAY call in %s"), *(GETENUMSTRING("ENetRole", GetLocalRole())));
		MulticastTest();

		if (GetLocalRole() == ROLE_Authority)
		{
			UE_LOG(LogTemp, Warning, TEXT("ServerOnly Client function BEGINPLAY call in %s"), *(GETENUMSTRING("ENetRole", GetLocalRole())));
			ClientTest();
			UE_LOG(LogTemp, Warning, TEXT("ServerOnly NetMulticast function BEGINPLAY call in %s"), *(GETENUMSTRING("ENetRole", GetLocalRole())));
			MulticastTest();
		}
	});

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, 5.0f, false);
}

void ADoor::OnConstruction(const FTransform& Transform)
{
	UE_LOG(LogTemp, Warning, TEXT("Construction"));
	if (AnimationOnOpenClose)
	{
		USkeletalMeshComponent* MeshComponent = GetSkeletalMeshComponent();
		float PlayRate = bIsOpen ? 1.0f : -1.0f;
		float Length = PlayRate * AnimationOnOpenClose->GetPlayLength();
		UE_LOG(LogTemp, Warning, TEXT("Construction %f %d"), Length, bIsOpen);
		MeshComponent->OverrideAnimationData(AnimationOnOpenClose, false, true, Length, PlayRate);
	}
}

void ADoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADoor, bIsOpen);
}

void ADoor::ServerSetIsOpen_Implementation(bool bNewIsOpen)
{
	if (bNewIsOpen == bIsOpen)
	{
		return;
	}

	bIsOpen = bNewIsOpen;
	if (GetLocalRole() == ROLE_Authority)
	{
		OnRep_IsOpen(!bIsOpen);
	}
}

void ADoor::OnRep_IsOpen(bool bOldIsOpen)
{
	if (bIsOpen == bOldIsOpen)
	{
		return;
	}

	USkeletalMeshComponent* MeshComponent = GetSkeletalMeshComponent();
	if (MeshComponent->HasValidAnimationInstance())
	{
		float PlayRate = bIsOpen ? 1.0f : -1.0f;
		MeshComponent->SetPlayRate(PlayRate);

		if (!MeshComponent->IsPlaying())
		{
			MeshComponent->Play(false);
		}
	}
}

