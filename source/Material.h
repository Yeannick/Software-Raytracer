#pragma once
#include "EMath.h"
#include "ERGBColor.h"
using namespace Elite;
class Material
{
public:
	Material();
	virtual ~Material() = default;
	Material(const Material&) = delete;
	Material(Material&&) noexcept = delete;
	Material& operator=(const Material&) = delete;
	Material& operator=(Material&&) noexcept = delete;

	virtual RGBColor Shade(const FVector3& hitrecord, const FVector3& v, const FVector3& l) const = 0;

};

