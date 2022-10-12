#include "PBRMaterial.h"
#include "BRDF.h"
#include <iostream>

PBRMaterial::PBRMaterial(float roughness, RGBColor albedo, bool isMetal) :
	m_Roughess{ roughness },
	m_Albedo{ albedo },
	m_Metalness{ isMetal }
{
}

RGBColor PBRMaterial::Shade(const FVector3& hitrecord, const Elite::FVector3& v, const Elite::FVector3& l) const
{
	RGBColor f0;

	if (!m_Metalness)
	{
		f0 = RGBColor{ 0.04f,0.04f,0.04f };
	}
	else
	{
		f0 = m_Albedo;
	}

	FVector3 halfVector{ GetNormalized(l + v) };
	RGBColor fresnel = BRDF::Fresnel(halfVector, v, f0);
	float normalDistribution = BRDF::NormalDistribution(hitrecord, halfVector, Square(m_Roughess));
	float kDirect = (Square(m_Roughess + 1)) / 8.f;
	//float kInDirect = Square(m_Roughess) / 2;
	float geometry = BRDF::Geometric(hitrecord, v, kDirect) * BRDF::Geometric(hitrecord, l, kDirect);
	RGBColor kd{};
	//std::cout << (4 * (Dot(v, hitrecord) * (Dot(l, hitrecord)))) << std::endl;
	RGBColor specular = (fresnel * normalDistribution * geometry) / (4 * (Dot(v, hitrecord) * (Dot(l, hitrecord))));

	if (!m_Metalness)
	{
		kd = Elite::RGBColor{ 1.f,1.f,1.f } - fresnel;
	}
	else
	{
		kd = Elite::RGBColor{ 0.f,0.f,0.f };
	}

	RGBColor diffuse = BRDF::Lambert(kd.r, m_Albedo);

	return diffuse + specular;
}
