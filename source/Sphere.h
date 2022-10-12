#pragma once
#include "Primitive.h"
#include <memory>
class Sphere final : public Primitive
{
public:
	Sphere(Elite::FPoint3 origin, float radius, Elite::RGBColor color, Material* material);
	virtual ~Sphere() = default;
	Sphere(const Sphere&) = delete;
	Sphere(Sphere&&) noexcept = delete;
	Sphere& operator=(const Sphere&) = delete;
	Sphere& operator=(Sphere&&) noexcept = delete;
	bool Hit(const Ray& ray, HitRecord& hitrecord, bool isShadow)  override;

private:
	float m_Radius;
};

