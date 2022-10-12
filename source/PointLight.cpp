#include "PointLight.h"

PointLight::PointLight(Elite::RGBColor color, float intensity, Elite::FPoint3 origin):
	Light{color,intensity},
	m_Origin{origin}
{
}
Elite::RGBColor PointLight::GetBiRadiance(const Elite::FPoint3& pointToShade) const
{
    return m_Color * (m_Intensity / SqrDistance(m_Origin, pointToShade));
}

Elite::FVector3 PointLight::GetDirection(const Elite::FPoint3& point) const
{
    return GetNormalized(m_Origin - point);
}

float PointLight::GetDistance(const Elite::FPoint3& point) const
{
    return Elite::Magnitude(point- m_Origin);
}