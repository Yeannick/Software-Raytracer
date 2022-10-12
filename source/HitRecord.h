#pragma once
#include "EMath.h"
#include "ERGBColor.h"
#include "Material.h"
struct HitRecord
{
	HitRecord();
	~HitRecord();

	Elite::FPoint3 intersectionPoint{};
	Elite::FVector3 normal{};
	Elite::RGBColor color{};
	float t { FLT_MAX };

	// raw pointer is fine because we are not talking about ownership here
	Material* m_pMaterial;

};