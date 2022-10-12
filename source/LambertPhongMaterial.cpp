#include "LambertPhongMaterial.h"
#include "BRDF.h"

LambertPhongMaterial::LambertPhongMaterial(float diffuseReflectance, RGBColor diffuseColor, float specularReflection, int exponent):
	m_DiffuseReflectance{ diffuseReflectance },
	m_DiffuseColor{ diffuseColor },
	m_SpecularReflection{ specularReflection },
	m_PhongExponent{ exponent }
{
}

RGBColor LambertPhongMaterial::Shade(const FVector3& hitrecord, const FVector3& v, const FVector3& l) const
{
	return BRDF::Lambert(m_DiffuseReflectance, m_DiffuseColor) + BRDF::Phong(m_SpecularReflection, m_PhongExponent, l, v, hitrecord);
}

