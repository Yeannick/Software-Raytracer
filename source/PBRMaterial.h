#pragma once
#include "Material.h"
class PBRMaterial final : public Material
{
public:
	PBRMaterial(float roughness, RGBColor albedo, bool isMetal);
	virtual ~PBRMaterial() = default;

	PBRMaterial(const PBRMaterial&) = delete;
	PBRMaterial(PBRMaterial&&) noexcept = delete;
	PBRMaterial& operator=(const PBRMaterial&) = delete;
	PBRMaterial& operator=(PBRMaterial&&) noexcept = delete;

	virtual RGBColor Shade(const FVector3 & hitrecord, const FVector3 & v, const FVector3 & l) const override;
private:
	float m_Roughess;
	RGBColor m_Albedo;
	bool m_Metalness;

};




