#pragma once
#include "Material.h"
class LambertPhongMaterial final : public Material
{
public:

    LambertPhongMaterial(float diffuseReflectance, RGBColor diffuseColor, float specularReflection, int exponent);
    virtual ~LambertPhongMaterial() = default;

    LambertPhongMaterial(const LambertPhongMaterial&) = delete;
    LambertPhongMaterial(LambertPhongMaterial&&) noexcept = delete;
    LambertPhongMaterial& operator=(const LambertPhongMaterial&) = delete;
    LambertPhongMaterial& operator=(LambertPhongMaterial&&) noexcept = delete;

    virtual RGBColor Shade(const FVector3& hitrecord, const FVector3& v, const FVector3& l) const override;

private:

    float m_DiffuseReflectance;
    RGBColor m_DiffuseColor;
    float m_SpecularReflection;
    int m_PhongExponent;
};

