// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvWeb.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Docking/TabManager.h"

#define LOCTEXT_NAMESPACE "AdvWeb"

void UAdvWeb::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UAdvWeb::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	
}

const FText UAdvWeb::GetPaletteCategory()
{
	return LOCTEXT("AdvWeb", "AdvWebType");
}

TSharedRef<SWidget> UAdvWeb::RebuildWidget()
{

	MyWindow = SNew(SWindow);


	FGlobalTabmanager::Get()->SetRootWindow(MyWindow.ToSharedRef());
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner("AAAAAA", FOnSpawnTab::CreateUObject(this, &UAdvWeb::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("BBBBB", "AdvWeb"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	
	
	MyDockTab = SNew(SDockTab)
		//.Label(FText::FromString(TEXT("AAAAA")))
		//.OnCanCloseTab(SDockTab::FCanCloseTab::CreateLambda([CanClose]()->bool {return CanClose; }))
		//.OnCloseButtonClicked(OnCloseButtonClicked)
		.TabRole(ETabRole::NomadTab)
		.ContentPadding(FMargin(0.f))
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("AdvWeb")))
		];

	MyTextBlock = SNew(STextBlock)
		.Text(FText::FromString(TEXT("AdvWeb")));
	return MyWindow.ToSharedRef();
}



TSharedRef<SDockTab> UAdvWeb::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTestLayoutWindowModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("TestLayoutWindow.cpp"))
	);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(WidgetText)
		]
		];
	
}

#undef LOCTEXT_NAMESPACE

