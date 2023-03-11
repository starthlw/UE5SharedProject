#include "AntAssetEditor.h"
#include "Styling/SlateStyleRegistry.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "AntAssetTestStyle.h"
#include "EditorViewportTabContent.h"
#include "EditorViewportLayout.h"
#include "EditorViewportCommands.h"
#include "AntAssetEditorCommands.h"
#include "AntAssetEditorViewport.h"

#define LOCTEXT_NAMESPACE "AntAssetEditorToolkit"

const FName FAntAssetEditorToolkit::ViewportTabId(TEXT("AntAssetEditor_Viewport"));
const FName FAntAssetEditorToolkit::PropertiesTabId(TEXT("AntAssetEditor_Properties"));

void FAntAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_AntAssetEditor", "AntAsset Editor"));
    auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

    FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

    InTabManager->RegisterTabSpawner(ViewportTabId, FOnSpawnTab::CreateSP(this, &FAntAssetEditorToolkit::SpawnTab_Viewport))
        .SetDisplayName(LOCTEXT("ViewportTab", "Viewport"))
        .SetGroup(WorkspaceMenuCategoryRef)
        .SetIcon(FSlateIcon(FAppStyle::Get().GetStyleSetName(), "LevelEditor.Tabs.Viewports"));

    InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FAntAssetEditorToolkit::SpawnTab_Properties))
        .SetDisplayName(LOCTEXT("PropertiesTab", "Details"))
        .SetGroup(WorkspaceMenuCategoryRef)
        .SetIcon(FSlateIcon(FAppStyle::Get().GetStyleSetName(), "LevelEditor.Tabs.Details"));
}

void FAntAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

    InTabManager->UnregisterTabSpawner(ViewportTabId);
    InTabManager->UnregisterTabSpawner(PropertiesTabId);
}

void FAntAssetEditorToolkit::InitAntAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit)
{
    AntAsset = CastChecked<UAntAsset>(ObjectToEdit);
    {
        AntAsset->PostEditCallback.Unbind();
        AntAsset->PostEditCallback.BindLambda([this]()
            {
                AntAssetViewport->UpdateViewport(SharedThis(this));
            });
    }
    AntAssetViewport = SNew(SAntAssetEditorViewport).AntAssetEditorToolkit(SharedThis(this));

    FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

    FDetailsViewArgs DetailsViewArgs;
    DetailsViewArgs.bAllowSearch = true;
    DetailsViewArgs.bLockable = false;
    DetailsViewArgs.bUpdatesFromSelection = false;
    DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
    DetailsViewArgs.NotifyHook = this;

    AntAssetDetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
    AntAssetDetailsView->SetObject(AntAsset);
    AntAssetDetailsView->OnFinishedChangingProperties().AddSP(this, &FAntAssetEditorToolkit::OnPropertyChanged);

    const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_AntAssetEditor_Layout_v2")
        ->AddArea
        (
            FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
            ->Split
            (
                FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
                ->Split
                (
                    FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
                    ->SetSizeCoefficient(0.9f)
                    ->Split
                    (
                        FTabManager::NewStack()
                        ->SetSizeCoefficient(0.6f)
                        ->AddTab(ViewportTabId, ETabState::OpenedTab)
                        ->SetHideTabWell(true)
                    )
                    ->Split
                    (
                        FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
                        ->SetSizeCoefficient(0.2f)
                        ->Split
                        (
                            FTabManager::NewStack()
                            ->SetSizeCoefficient(0.7f)
                            ->AddTab(PropertiesTabId, ETabState::OpenedTab)
                        )
                    )
                )
            )
        );

    const bool bCreateDefaultStandaloneMenu = true;
    const bool bCreateDefaultToolbar = true;
    FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, FName(TEXT("AntAssetEditorApp")), StandaloneDefaultLayout, bCreateDefaultToolbar, bCreateDefaultStandaloneMenu, ObjectToEdit);
}

void FAntAssetEditorToolkit::ExtendToolbar()
{
    TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

    ToolbarExtender->AddToolBarExtension(
        "Asset",
        EExtensionHook::After,
        GetToolkitCommands(),
        FToolBarExtensionDelegate::CreateSP(this, &FAntAssetEditorToolkit::FillToolbar, GetToolkitCommands())
    );

    AddToolbarExtender(ToolbarExtender);
}

void FAntAssetEditorToolkit::FillToolbar(FToolBarBuilder& ToolbarBuilder, const TSharedRef<FUICommandList> InToolkitCommands)
{
    const ISlateStyle* UIStyle = FSlateStyleRegistry::FindSlateStyle(FAntAssetTestStyle::GetStyleSetName());

    ToolbarBuilder.BeginSection("AntAsset");
    {
    }
    ToolbarBuilder.EndSection();
}

void FAntAssetEditorToolkit::BindCommands()
{
    const FAntAssetEditorCommands& Commands = FAntAssetEditorCommands::Get();
    const TSharedRef<FUICommandList>& UICommandList = GetToolkitCommands();
    // todo
}

TSharedRef<SDockTab> FAntAssetEditorToolkit::SpawnTab_Properties(const FSpawnTabArgs& Args)
{
    check(Args.GetTabId() == PropertiesTabId);

    return SNew(SDockTab)
        .Label(LOCTEXT("AntAssetEditorProperties_TabTitle", "Details"))
        [
            AntAssetDetailsView.ToSharedRef()
        ];
}

TSharedRef<SDockTab> FAntAssetEditorToolkit::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
    TSharedRef< SDockTab > DockableTab =
        SNew(SDockTab);

    ViewportTabContent = MakeShareable(new FEditorViewportTabContent());
    const FString LayoutId = FString("AntAssetEditorViewport");

    ViewportTabContent->Initialize([this](const FAssetEditorViewportConstructionArgs& InConstructionArgs)
        {
            return AntAssetViewport.ToSharedRef();
        }, DockableTab, LayoutId);
    return DockableTab;
}

void FAntAssetEditorToolkit::OnPropertyChanged(const FPropertyChangedEvent& InEvent)
{
    AntAsset->PostEditCallback.ExecuteIfBound();
}

FName FAntAssetEditorToolkit::GetToolkitFName() const
{
    return FName("AntAssetEditor");
}

FText FAntAssetEditorToolkit::GetBaseToolkitName() const
{
    return LOCTEXT("AppLabel", "AntAsset Editor");
}

FString FAntAssetEditorToolkit::GetWorldCentricTabPrefix() const
{
    return LOCTEXT("WorldCentricTabPrefix", "AntAsset ").ToString();
}

FLinearColor FAntAssetEditorToolkit::GetWorldCentricTabColorScale() const
{
    return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

void FAntAssetEditorToolkit::AddReferencedObjects(FReferenceCollector& Collector)
{
}

TSharedPtr<FAntAssetEditorToolkit> FAntAssetEditorToolkit::CreateEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitTookitHost, UObject* ObjectToEdit)
{
    TSharedPtr<FAntAssetEditorToolkit> NewEditor = MakeShareable(new FAntAssetEditorToolkit());
    NewEditor->InitAntAssetEditor(Mode, InitTookitHost, ObjectToEdit);

    return NewEditor;
}

#undef LOCTEXT_NAMESPACE
