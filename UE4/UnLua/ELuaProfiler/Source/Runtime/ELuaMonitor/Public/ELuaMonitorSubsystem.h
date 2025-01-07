// *********************************************************************
// Copyright 1998-2026 Tencent Games, Inc. All Rights Reserved.
// 作      者：gershonchen
// 创建日期：2024年07月23日
// 功能描述：
// *********************************************************************

#pragma once

#include "Subsystems/WorldSubsystem.h"
#include "ELuaMonitorSubsystem.generated.h"

UCLASS(MinimalAPI)
class UELuaMonitorWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void PostInitialize() override;

	void Deinitialize() override;
};