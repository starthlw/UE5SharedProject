// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Toolkits/BaseToolkit.h"
#include "AntTestEdMode.h"

class SAntTestEditor;

class FAntTestEdModeToolkit : public FModeToolkit
{
public:
	virtual void Init(const TSharedPtr< class IToolkitHost >& InitToolkitHost) override;
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FAntTestEdMode* GetEditorMode() const override;
	void RefreshDetailPanel();

	TSharedPtr<class FUICommandList> GetToolkitCommands() const;
	TSharedPtr<SWidget> GetInlineContent() const;

	TSharedPtr<SAntTestEditor> AntTestEditor;
};

class SAntTestEditor : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAntTestEditor) {}
	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs, TSharedRef<FAntTestEdModeToolkit> InParentToolkit);
	bool GetEditorIsEnabled() const;
	void RefreshDetailPanel();

protected:
	bool GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;

protected:
	FAntTestEdMode* GetEditorMode() const;

	TWeakPtr<FAntTestEdModeToolkit> ParentToolkit;
	TSharedPtr<IDetailsView> DetailsPanel;
};
