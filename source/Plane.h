#pragma once
#include "Primitive.h"
#include <memory>
class Plane final :public Primitive
{
public:
	Plane(FPoint3 origin, FVector3 normal, RGBColor color, Material* material);
	virtual ~Plane() = default;

	Plane(const Plane&) = delete;
	Plane(Plane&&) noexcept = delete;
	Plane& operator=(const Plane&) = delete;
	Plane& operator=(Plane&&) noexcept = delete;

	bool Hit(const Ray & ray, HitRecord & hitrecord, bool isShadow) override;
private:
	FVector3 m_Normal{};
};

