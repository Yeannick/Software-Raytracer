#include "BRDF.h"

RGBColor BRDF::Lambert(const float DiffuseReflectance, const RGBColor DiffuseColor)
{
	return (DiffuseColor * DiffuseReflectance / float(E_PI));
}
RGBColor BRDF::Phong(const float specularReflectance, const int phongExponent, const FVector3 l, const FVector3 v, const FVector3 normal)
{
	FVector3 Lnormal{ 2 * std::max(Dot(normal , l),0.0f) * normal };
	FVector3 reflect = l - (Lnormal);
	float cosAlpha = std::max(Dot(reflect, v),0.0f);
	float phongSpecularReflection = specularReflectance * pow(cosAlpha, phongExponent);
	return RGBColor(phongSpecularReflection, phongSpecularReflection, phongSpecularReflection);
}

float BRDF::NormalDistribution(const FVector3 normal, const FVector3 halfvector, const float a)
{
	float a2 = Square(a);
	float dotSquared = Square(Dot(normal, halfvector));
	float roughnessPart = a2 - 1;
	float normaldistribution = a2 / (E_PI * Square(dotSquared * roughnessPart + 1));
	return normaldistribution;
}

RGBColor BRDF::Fresnel(const FVector3 halfvector, const FVector3 viewDirection, const RGBColor f0)
{
	RGBColor Color1{ 1.f,1.f,1.f };

	float dotend{ 1 - (std::max(Dot(halfvector,viewDirection),0.0f)) };
	float PowDot = float(pow(dotend, 5));
	return f0 + ((Color1 - f0) * PowDot);
}

float BRDF::Geometric(const FVector3 normal, const FVector3 viewDirection, float k)
{
	float normalV{ std::max(Dot(normal,viewDirection),0.0f) };
	float geometric = normalV /( (normalV) * (1 - k) + k);
	return geometric;
}
