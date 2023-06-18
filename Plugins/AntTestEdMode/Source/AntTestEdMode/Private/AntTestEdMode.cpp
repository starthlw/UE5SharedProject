// Copyright Epic Games, Inc. All Rights Reserved.

#include "AntTestEdMode.h"
#include "AntTestEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"

#include "EditorModeManager.h"
#include "Selection.h"

#include "Landscape.h"
#include "LandscapeHeightfieldCollisionComponent.h"
#include "LandscapeDataAccess.h"
#include "LandscapeComponent.h"
#include "LandscapeInfo.h"
#include "LandscapeSubsystem.h"

#include "LevelEditorViewport.h"

#include "EditorModes.h"
#include "EditorModeManager.h"
#include "EngineUtils.h"

#include "AntTestEdModeObject.h"

const FEditorModeID FAntTestEdMode::EM_AntTestEdModeId = TEXT("EM_AntTest");

FAntTestEdMode::FAntTestEdMode()
{
	Toolkit = MakeShareable(new FAntTestEdModeToolkit);

    UISettings = NewObject<UAntTestEdModeObject>(GetTransientPackage(), TEXT("AntTestUISettings"), RF_Transactional);
    UISettings->SetParent(this);
}

void FAntTestEdMode::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdMode::AddReferencedObjects(Collector);
}

void FAntTestEdMode::Enter()
{
	FEdMode::Enter();

	{
		Toolkit = MakeShareable(new FAntTestEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FAntTestEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	FEdMode::Exit();
}

void FAntTestEdMode::Render(const FSceneView *View, FViewport *Viewport, FPrimitiveDrawInterface *PDI)
{
	// You can do any rendering during your custom editor mode here
}

bool FAntTestEdMode::HandleClick(FEditorViewportClient *InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click)
{
	if (InViewportClient)
	{
		FHitResult HitResult;
        auto Origin = Click.GetOrigin();
        auto RayDirection = Click.GetOrigin() + Click.GetDirection() * WORLD_MAX;
		if (InViewportClient->GetWorld()->LineTraceSingleByObjectType(HitResult, Origin, RayDirection, FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic)))
		{
			FVector HitLocation = HitResult.Location;
			UE_LOG(LogTemp, Log, TEXT("HandleClick Hit Location: %s"), *HitLocation.ToString());

			UWorld *World = InViewportClient->GetWorld();
			const FRotator Rotation = FVector::ZeroVector.Rotation();
			AStaticMeshActor *Cube = World->SpawnActor<AStaticMeshActor>(HitLocation, Rotation);
			if (UISettings->Mesh)
			{
				Cube->GetStaticMeshComponent()->SetStaticMesh(UISettings->Mesh);
			}
		}
	}
	return false;
}

void FAntTestEdMode::RefreshDetailPanel()
{
	if (Toolkit.IsValid())
	{
		StaticCastSharedPtr<FAntTestEdModeToolkit>(Toolkit)->RefreshDetailPanel();
	}
}

