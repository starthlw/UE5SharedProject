// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "AntTestEdMode.h"

#include "AntTestEdModeObject.generated.h"

UCLASS()
class UAntTestEdModeObject : public UObject
{
	GENERATED_UCLASS_BODY()

	FAntTestEdMode* ParentMode;

public:
    UPROPERTY(Category = "Procedural", EditAnywhere)
    TObjectPtr<UStaticMesh> Mesh;


#if WITH_EDITOR
    //~ Begin UObject Interface
    void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
    //~ End UObject Interface
#endif // WITH_EDITOR

    void SetParent(FAntTestEdMode* Parent)
    {
        ParentMode = Parent;
    }
};
