#include "LambertMaterial.h"
#include "BRDF.h"

LambertMaterial::LambertMaterial(float diffuseReflectance, RGBColor diffuseColor) :
	m_DiffuseReflectance{ diffuseReflectance },
	m_DiffuseColor{ diffuseColor }
{
}

RGBColor LambertMaterial::Shade(const FVector3& hitrecord, const FVector3& v, const FVector3& l) const
{
	return BRDF::Lambert(m_DiffuseReflectance, m_DiffuseColor);
}
