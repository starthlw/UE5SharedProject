// Copyright Epic Games, Inc. All Rights Reserved.

#include "AntTestEdModeObject.h"

UAntTestEdModeObject::UAntTestEdModeObject(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UAntTestEdModeObject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
}
