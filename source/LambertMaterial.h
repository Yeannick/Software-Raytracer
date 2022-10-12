#pragma once
#include "Material.h"
class LambertMaterial final :public Material
{
public:
    LambertMaterial(float diffuseReflectance, RGBColor diffuseColor);
    virtual ~LambertMaterial() = default;
    LambertMaterial(const LambertMaterial&) = delete;
    LambertMaterial(LambertMaterial&&) noexcept = delete;
    LambertMaterial& operator=(const LambertMaterial&) = delete;
    LambertMaterial& operator=(LambertMaterial&&) noexcept = delete;

    virtual RGBColor Shade(const FVector3 & hitrecord, const FVector3 & v, const FVector3 & l) const override;

private:

    float m_DiffuseReflectance;
    RGBColor m_DiffuseColor;
};

