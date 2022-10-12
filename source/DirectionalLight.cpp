#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(const Elite::RGBColor& color, float intensity, const Elite::FVector3& direction) :
	Light{ color,intensity },
	m_Direction{ GetNormalized(direction) }
{
}

Elite::RGBColor DirectionalLight::GetBiRadiance(const Elite::FPoint3& pointToShade) const
{
	return m_Color * m_Intensity;
}

Elite::FVector3 DirectionalLight::GetDirection(const Elite::FPoint3& point) const
{
	return -m_Direction;
}

float DirectionalLight::GetDistance(const Elite::FPoint3& point) const
{
	return FLT_MAX;
}
