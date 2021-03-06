// Copyright Epic Games, Inc. All Rights Reserved.

#include "KizuEngine.h"

#define LOCTEXT_NAMESPACE "FKizuEngineModule"

void FKizuEngineModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FKizuEngineModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FKizuEngineModule, KizuEngine)

//General Log
DEFINE_LOG_CATEGORY(LogKizu);

//Logging during sessions and game Initialization phase
DEFINE_LOG_CATEGORY(LogKizuInit);

//Logging for your AI system
DEFINE_LOG_CATEGORY(LogKizuAI);