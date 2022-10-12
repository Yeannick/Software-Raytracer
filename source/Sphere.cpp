#include "Sphere.h"

Sphere::Sphere(Elite::FPoint3 origin, float radius, Elite::RGBColor color , Material* material) :
	Primitive{origin,color,material},
	m_Radius{radius}
{
}


bool Sphere::Hit(const Ray& ray, HitRecord& hitrecord, bool isShadow) 
{
	FVector3 origin = ray.origin - m_Origin;
	FVector3 bRay = (2 * ray.direction);

	float a = Dot(ray.direction, ray.direction);
	float b = Dot(bRay, origin);
	float c = Dot(origin, origin) - (m_Radius * m_Radius);
	float discriminant = ((b * b) - (4.f * a * c));

	if (discriminant > 0)
	{
		float a2{ 2.f * a };

		float sqrtDiscriminant{ sqrt(discriminant) };
		float t{ (-b - sqrtDiscriminant) / a2 };
		if (t < ray.tMin)
		{
			t = (-b + sqrtDiscriminant) / a2;
		}

		if (!(t < ray.tMin || t > ray.tMax))
		{
			hitrecord.t = t;
			hitrecord.intersectionPoint = ray.origin + t * ray.direction;
			hitrecord.normal = (hitrecord.intersectionPoint - m_Origin) / m_Radius;
			hitrecord.color = m_Color;
			hitrecord.m_pMaterial = m_pMaterial;
			return true;
		}
	}



	return false;
}