#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Factories/Factory.h"
#include "AntAssetFactory.generated.h"

UCLASS()
class UAntAssetFactory : public UFactory
{
    GENERATED_BODY()

public:
    UAntAssetFactory();

    virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
    virtual FText GetToolTip() const override;
};