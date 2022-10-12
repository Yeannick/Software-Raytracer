#include "Plane.h"

Plane::Plane(FPoint3 origin, FVector3 normal, RGBColor color, Material* material):
	Primitive{origin,color,material },
	m_Normal{normal}
{
}

bool Plane::Hit(const Ray& ray, HitRecord& hitrecord, bool isShadow) 
{
	float t;

	t = Dot((m_Origin - ray.origin), m_Normal) / Dot(ray.direction, m_Normal);


	if (t > ray.tMin && t < ray.tMax)
	{
		hitrecord.intersectionPoint = ray.origin + t * ray.direction;
		hitrecord.t = t;
		hitrecord.normal = m_Normal;
		hitrecord.color = m_Color;
		hitrecord.m_pMaterial = m_pMaterial;
		return true;
	}

	return false;
}
