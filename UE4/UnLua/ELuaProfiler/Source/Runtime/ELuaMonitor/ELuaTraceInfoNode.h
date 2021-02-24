// The MIT License (MIT)

// Copyright 2020 HankShu inkiu0@gmail.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include "LuaCore/ELuaBase.h"

struct ELUAPROFILER_API FELuaTraceInfoNode
{
	/* show name */
	FString Name = "anonymous";

	/* call time */
	double CallTime = 0;

	/* self time */
	double SelfTime = 0;

	/* total time */
	double TotalTime = 0;

	/* average time */
	double Average = 0;

	/* the total size of lua_State when this node invoke */
	float CallSize = 0;

	/* the total size of lua_State when this node return */
	//int32 ReturnSize;

	/* the size of this node alloc */
	float AllocSize = 0;

	/* the size of this node release */
	float GCSize = 0;

	/* the num of calls */
	int32 Count = 0;

	/* debug info event 
	 * LUA_HOOKCALL
	 * LUA_HOOKRET 
	 * LUA_HOOKTAILCALL
	 * LUA_HOOKLINE
	 * LUA_HOOKCOUNT
	 */
	int32 Event = -1;

	/* node id */
	FString ID;

	/* parent node */
	TSharedPtr<FELuaTraceInfoNode> Parent = nullptr;

	/* all child nodes */
	TArray<TSharedPtr<FELuaTraceInfoNode>> Children;

	/* id map to FELuaTraceInfoNode */
	TMap<FString, TSharedPtr<FELuaTraceInfoNode>> ChildIDMap;

	FELuaTraceInfoNode(TSharedPtr<FELuaTraceInfoNode> InParent, FString& InID, const char* InName, int32 InEvent)
	{
		ID = InID;
		if (InName)
		{
			Name = InName;
		}
		Event = InEvent;
		Parent = InParent;
	}

	void AddChild(TSharedPtr<FELuaTraceInfoNode> Child)
	{
		Children.Add(Child);
		ChildIDMap.Add(Child->ID, Child);
	}

	// ֻ��Root�Ż����
	void FakeBeginInvoke()
	{
		CallTime = GetTimeMs();
		CallSize = GetStateMemKb();
	}

	// ֻ��Root��һ֡������δ���صĺ��������
	void FakeEndInvoke()
	{
		double NowTime = GetTimeMs();
		TotalTime += NowTime - CallTime;
		CallTime = NowTime;

		float NowSize = GetStateMemKb();
		int32 Increment = NowSize - CallSize;
		CallSize = NowSize;
		if (Increment > 0)
		{
			AllocSize += Increment;
		}
		else
		{
			GCSize += Increment;
		}
	}

	void BeginInvoke()
	{
		CallTime = GetTimeMs();
		CallSize = GetStateMemKb();
		Count += 1;
	}

	int32 EndInvoke()
	{
		TotalTime += GetTimeMs() - CallTime;

		int32 Increment = GetStateMemKb() - CallSize;
		if (Increment > 0)
		{
			AllocSize += Increment;
		} 
		else
		{
			GCSize += Increment;
		}
		return Event;
	}

	TSharedPtr<FELuaTraceInfoNode> GetChild(const FString& InID)
	{
		if (ChildIDMap.Contains(InID))
		{
			return ChildIDMap[InID];
		}
		return nullptr;
	}

	void Empty()
	{
		Name.Empty();
		CallTime = 0.f;
		SelfTime = 0.f;
		TotalTime = 0.f;
		Count = 0;
		Event = 0;
		ID.Empty();
		Parent = nullptr;
		Children.Empty();
		ChildIDMap.Empty();
	}

	FELuaTraceInfoNode(TSharedPtr<FELuaTraceInfoNode> Other)
	{
		ID = Other->ID;
		Name = Other->Name;
		CallTime = Other->CallTime;
		SelfTime = Other->SelfTime;
		TotalTime = Other->TotalTime;
		CallSize = Other->CallSize;
		AllocSize = Other->AllocSize;
		GCSize = Other->GCSize;
		Count = Other->Count;
		Event = Other->Event;
		Parent = Other->Parent;
	}

	void StatisticizeOtherNode(TSharedPtr<FELuaTraceInfoNode> Other)
	{
		if (ChildIDMap.Contains(Other->ID))
		{
			TSharedPtr<FELuaTraceInfoNode> CNode = ChildIDMap[Other->ID];
			CNode->SelfTime += Other->SelfTime;
			CNode->TotalTime += Other->TotalTime;
			CNode->AllocSize += Other->AllocSize;
			CNode->GCSize += Other->GCSize;
			CNode->Count += Other->Count;
		}
		else
		{
			AddChild(TSharedPtr<FELuaTraceInfoNode>(new FELuaTraceInfoNode(Other)));
		}
		TotalTime += Other->TotalTime;
		AllocSize += Other->AllocSize;
		GCSize += Other->GCSize;
	}
};
