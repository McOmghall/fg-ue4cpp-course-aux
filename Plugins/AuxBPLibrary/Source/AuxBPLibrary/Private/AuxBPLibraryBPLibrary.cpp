// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AuxBPLibraryBPLibrary.h"
#include "AuxBPLibrary.h"

UAuxBPLibraryBPLibrary::UAuxBPLibraryBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

int UAuxBPLibraryBPLibrary::FilterArray(const FSelectDelegate& FilterSelect, const TArray<UObject*> InArray, TArray<UObject*>& OutArray)
{
	if (!FilterSelect.IsBound())
	{
		OutArray = TArray<UObject*>();
		return 0;
	}

	for (UObject* Object : InArray)
	{
		if (FilterSelect.Execute(Object))
		{
			OutArray.Add(Object);
		}
	}

	return OutArray.Num();
}

