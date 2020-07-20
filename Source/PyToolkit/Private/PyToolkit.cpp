// Copyright Epic Games, Inc. All Rights Reserved.

#include "PyToolkit.h"

#define LOCTEXT_NAMESPACE "FPyToolkitModule"

void FPyToolkitModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Initialize the tick handler
	TickHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([this](float DeltaTime)
	{
		Tick(DeltaTime);
		return true;
	}));

}

void FPyToolkitModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

}

void FPyToolkitModule::Tick(const float InDeltaTime) {
	// �ο� Python �ٷ���� | �����ʼ�����֮�� ͨ�� tick ����ʼ�� initialize.py �ű�
	if (!bHasTicked) {
		bHasTicked = true;
		FString InitScript = TEXT("py \"") + FPaths::ProjectPluginsDir() / TEXT("PyToolkit/Content/initialize.py") + TEXT("\"");
		GEngine->Exec(NULL, InitScript.GetCharArray().GetData());
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPyToolkitModule, PyToolkit)