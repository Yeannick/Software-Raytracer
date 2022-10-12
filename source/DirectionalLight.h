#pragma once
#include "Light.h"
using namespace Elite;

class DirectionalLight final : public Light
{
public:
	DirectionalLight(const Elite::RGBColor& color, float intensity, const Elite::FVector3& direction);
	virtual ~DirectionalLight() = default;

	DirectionalLight(const DirectionalLight&) = delete;
	DirectionalLight(DirectionalLight&&) noexcept = delete;
	DirectionalLight& operator=(const DirectionalLight&) = delete;
	DirectionalLight& operator=(DirectionalLight&&) noexcept = delete;

	virtual Elite::RGBColor GetBiRadiance(const Elite::FPoint3& pointToShade) const override;
	virtual Elite::FVector3 GetDirection(const Elite::FPoint3& point) const override;
	virtual float GetDistance(const Elite::FPoint3& point) const override;

private:
	Elite::FVector3 m_Direction;
};

