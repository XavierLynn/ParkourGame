// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "AdvWeb.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEWEB_API UAdvWeb : public UWidget
{
	GENERATED_BODY()
public:

	DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SDockTab>, FOnSpawnTab, const FSpawnTabArgs&);

	virtual void SynchronizeProperties() override;
	

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#if WITH_EDITOR
	//~ Begin UWidget Interface
	virtual const FText GetPaletteCategory() override;
	//~ End UWidget Interface
#endif

protected:
	

	virtual TSharedRef<SWidget> RebuildWidget() override;

	TSharedPtr<class SDockTab> MyDockTab;
	TSharedPtr<STextBlock> MyTextBlock;
	TSharedPtr<SWindow> MyWindow;
	//TSharedPtr<class SWebBrowser> MEWebBrowser;


public:

	TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);
};
