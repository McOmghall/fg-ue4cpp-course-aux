// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckPlayerVisible.h"
#include "../StateMachineExampleCharacter.h"

#include "DrawDebugHelpers.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Kismet/GameplayStatics.h"

void UBTService_CheckPlayerVisible::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard == nullptr)
	{
		return;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(OwnerComp.GetWorld(), 0);
	AActor* PlayerPawn = PlayerController ? PlayerController->GetPawn() : nullptr;
	AActor* ControlledPawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;

	if (PlayerPawn == nullptr || ControlledPawn == nullptr)
	{
		return;
	}

	// Check if it's in front of
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector OwnLocation = ControlledPawn->GetActorLocation();
	FVector DirectionToPlayer = (PlayerLocation - OwnLocation).GetSafeNormal();
	float DotProduct = FVector::DotProduct(DirectionToPlayer, ControlledPawn->GetActorForwardVector());
	float AngleLimit = FMath::Cos(FMath::DegreesToRadians(AngleTolerance));
	bool bPlayerIsInFront = AngleLimit <= DotProduct;

	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	QueryParams.AddIgnoredActor(ControlledPawn);
	FHitResult OutHit;
	bool bHit = bPlayerIsInFront && OwnerComp.GetWorld()->LineTraceSingleByChannel(OutHit, ControlledPawn->GetActorLocation(), PlayerPawn->GetActorLocation(), ECollisionChannel::ECC_Visibility, QueryParams);
	if (bHit)
	{
		AActor* ActorHit = OutHit.Actor.Get();
		bHit = ActorHit != nullptr && ActorHit->IsValidLowLevel() && !ActorHit->IsPendingKill() && ActorHit->IsA<AStateMachineExampleCharacter>();
		bHit = bHit && Blackboard->SetValue<UBlackboardKeyType_Object>(BlackboardKey.SelectedKeyName, ActorHit);
	}

	// Debug config
	bool bPersistent = false;
	float LifeTime = 5.0f;
	FColor GoodColor = FColor::Green;
	FColor BadColor = FColor::Red;
	float ImpactPointSize = 16.0f;
	if (bHit && OutHit.bBlockingHit)
	{
		// Red up to the blocking hit, green thereafter
		DrawDebugLine(GetWorld(), ControlledPawn->GetActorLocation(), OutHit.ImpactPoint, BadColor, bPersistent, LifeTime);
		DrawDebugLine(GetWorld(), OutHit.ImpactPoint, PlayerPawn->GetActorLocation(), GoodColor, bPersistent, LifeTime);
		DrawDebugPoint(GetWorld(), OutHit.ImpactPoint, ImpactPointSize, GoodColor, bPersistent, LifeTime);
	}
	else
	{
		// no hit means all red
		DrawDebugLine(GetWorld(), ControlledPawn->GetActorLocation(), PlayerPawn->GetActorLocation(), BadColor, bPersistent, LifeTime);
	}
}