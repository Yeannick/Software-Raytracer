#pragma once
#include "EMath.h"
#include "ERGBColor.h"
#include "HitRecord.h"
#include "Ray.h"
#include <memory>

class Primitive
{
public:
	Primitive(Elite::FPoint3 origin, Elite::RGBColor color, Material* pMaterial);
	virtual ~Primitive() = default;
	Primitive(const Primitive&) = delete;
	Primitive(Primitive&&) noexcept = delete;
	Primitive& operator=(const Primitive&) = delete;
	Primitive& operator=(Primitive&&) noexcept = delete;

	virtual bool Hit(const Ray& ray, HitRecord& hitRecord,  bool isShadow) = 0;

	
protected:
	Elite::FPoint3 m_Origin{};
	Elite::RGBColor m_Color{};
	Material* m_pMaterial;
};

