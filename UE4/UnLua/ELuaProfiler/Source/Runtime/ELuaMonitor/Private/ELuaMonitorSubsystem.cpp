#include "ELuaMonitorSubsystem.h"

#include "ELuaMonitor.h"

void UELuaMonitorWorldSubsystem::PostInitialize()
{
	FELuaMonitorModule::GetInstance()->OnWorldAdded(GetWorld());
}

void UELuaMonitorWorldSubsystem::Deinitialize()
{
	FELuaMonitorModule::GetInstance()->OnWorldRemoved(GetWorld());
}