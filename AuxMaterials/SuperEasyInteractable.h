/**
 * THIS IS NOT A SOURCE FILE
 * ADD ELEMENTS AS DESCRIBED TO YOUR CODE BASE
 * READ THROUGH THE WHOLE DOCUMENT
 */

/**
 * CREATE NEW Interactable.h INTERFACE
 */
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class STATEMACHINEEXAMPLE_API IInteractable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	bool Interact(AActor* Interactor);
	virtual bool Interact_Implementation(AActor* Interactor) { return false; };
};

/**
 * END Interactable.h
 */

 /**
  * ADD INCLUDES TO <YourProjectCharacter>
  */

#include "DrawDebugHelpers.h"
#include "Interactable.h"

/**
 * ADD THE FOLLOWING OnInteract FUNCTION TO <YourProjectCharacter>
 */
void AStateMachineExampleCharacter::OnInteract()
{
	// World space
	FVector CameraLocation = FirstPersonCameraComponent->GetComponentLocation();
	FVector Offset = FirstPersonCameraComponent->GetForwardVector() * 500;
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	QueryParams.AddIgnoredActor(this);
	FHitResult OutHit;

	// Perfom trace
	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, CameraLocation, CameraLocation + Offset, ECollisionChannel::ECC_Visibility, QueryParams);

	if (bHit)
	{
		AActor* ActorHit = OutHit.Actor.Get();
		if (ActorHit != nullptr && ActorHit->IsValidLowLevel() && !ActorHit->IsPendingKill() && ActorHit->Implements<UInteractable>())
		{
			bHit = IInteractable::Execute_Interact(ActorHit, this);
		}
		else
		{
			bHit = false;
		}
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
		DrawDebugLine(GetWorld(), CameraLocation, OutHit.ImpactPoint, BadColor, bPersistent, LifeTime);
		DrawDebugLine(GetWorld(), OutHit.ImpactPoint, CameraLocation + Offset, GoodColor, bPersistent, LifeTime);
		DrawDebugPoint(GetWorld(), OutHit.ImpactPoint, ImpactPointSize, GoodColor, bPersistent, LifeTime);
	}
	else
	{
		// no hit means all red
		DrawDebugLine(GetWorld(), CameraLocation, CameraLocation + Offset, BadColor, bPersistent, LifeTime);
	}
}

/**
 * --> In editor: CREATE NEW INPUT ACTION MAPPING (Name "Interact" here)
 * ----> Project settings > Input > Action Mappings +
 *
 * THEN BIND INPUT IN <YourProjectCharacter>
 */
PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AYourProjectCharacter::OnInteract);

/**
 * SUBCLASS IInteract AND OVERRIDE Interact_Implementation IN C++
 * OR CREATE A BLUEPRINT ACTOR THAT IMPLEMENTS THE INTERFACE
 */
