// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ObjectMacros.h"
#include "AuxBPLibraryBPLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FSelectDelegate, UObject*, Object);

UCLASS()
class UAuxBPLibraryBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (Keywords = "AuxBPLibrary sample test testing", AutoCreateRefTerm = "FilterSelect, InArray"), Category = "AuxBPLibraryTesting")
	static int FilterArray(const FSelectDelegate& FilterSelect, const TArray<UObject*> InArray, TArray<UObject*>& OutArray);
};
