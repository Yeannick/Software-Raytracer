#pragma once
#include "EMath.h"
#include "ERGBColor.h"
class Light
{
public:
	Light(Elite::RGBColor color, float intensity);
	virtual ~Light() = default;
	Light(const Light&) = delete;
	Light(Light&&) noexcept = delete;
	Light& operator=(const Light&) = delete;
	Light& operator=(Light&&) noexcept = delete;

	virtual Elite::RGBColor GetBiRadiance(const Elite::FPoint3 & pointToShade) const = 0;
	virtual Elite::FVector3 GetDirection(const Elite::FPoint3 & point) const = 0;
	virtual float GetDistance(const Elite::FPoint3 & point) const = 0;

protected:
	const Elite::RGBColor m_Color{};
	const float m_Intensity{};
};

