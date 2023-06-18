// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"
#include "LandscapeInfo.h"
#include "LandscapeProxy.h"
#include "Landscape.h"

class UAntTestEdModeObject;

class FAntTestEdMode : public FEdMode
{
public:
	const static FEditorModeID EM_AntTestEdModeId;

public:
	FAntTestEdMode();
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	// FEdMode interface
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Render(const FSceneView *View, FViewport *Viewport, FPrimitiveDrawInterface *PDI) override;
	virtual bool HandleClick(FEditorViewportClient *InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click) override;

	void RefreshDetailPanel();

    UAntTestEdModeObject* UISettings;
};
