#pragma once
#include "EMath.h"
#include "ERGBColor.h"

using namespace Elite;
namespace BRDF
{
	RGBColor Lambert(const float DiffuseReflectance, const RGBColor DiffuseColor);

	RGBColor Phong(const float specularReflectance, const int phongExponent, const FVector3 l, const FVector3 v, const FVector3 normal);

	float NormalDistribution(const FVector3 normal, const FVector3 halfvector, const float a);

	RGBColor Fresnel(const FVector3 halfvector, const FVector3 viewDirection, const RGBColor f0);

	float Geometric(const FVector3 normal, const FVector3 viewDirection, float k);
};

