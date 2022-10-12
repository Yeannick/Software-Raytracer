#pragma once

#include "EMath.h"

using namespace Elite;
struct Ray
{
//------- DataMembers-------//
	FPoint3 origin = {};
	FVector3 direction = {};
	float tMin = 0.0001f;
	float tMax = FLT_MAX;
};