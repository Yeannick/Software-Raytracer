#pragma once
#include "Light.h"
class PointLight final :public Light
{
public :
	PointLight(Elite::RGBColor color, float intensity, Elite::FPoint3 origin);
	virtual ~PointLight() = default;

	PointLight(const PointLight&) = delete;
	PointLight(PointLight&&) noexcept = delete;
	PointLight& operator=(const PointLight&) = delete;
	PointLight& operator=(PointLight&&) noexcept = delete;

	virtual Elite::RGBColor GetBiRadiance(const Elite::FPoint3& pointToShade) const override;
	virtual Elite::FVector3 GetDirection(const Elite::FPoint3& point) const override;
	virtual float GetDistance(const Elite::FPoint3& point) const override;

private:
	Elite::FPoint3 m_Origin{};
};

