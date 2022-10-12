#pragma once
#include "Primitive.h"
#include <vector>
#include "ETimer.h"

using namespace Elite;
class Material;
enum CullMode
{
	none, frontFace, backFace
};
class Triangle final : public Primitive
{
public:
	Triangle(FPoint3 origin, std::vector<FPoint3>relativePoints, RGBColor color, Material* material, CullMode state);
	virtual ~Triangle() = default;
	Triangle(const Triangle&) = delete;
	Triangle(Triangle&&) noexcept = delete;
	Triangle& operator=(const Triangle&) = delete;
	Triangle& operator=(Triangle&&) noexcept = delete;

	bool Hit(const Ray & ray, HitRecord & hitrecord ,bool isShadow)  override;
	static bool Hit(const Ray& ray, HitRecord& hitRecord, bool isShadowRay, const CullMode& cullmode, const std::vector<FPoint3>& vertices, const FVector3& normal);
	//void Rotate(float angle);
	 CullMode GetCullMode()const ;
	 void SetCullMode(CullMode state);
private:
	std::vector<FPoint3>m_Vertices;
	CullMode m_CullMode{ none };
	Elite::Timer* pTimer;
	FVector3 m_Normal;


};

