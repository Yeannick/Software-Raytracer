#include "Triangle.h"

using namespace Elite;

Triangle::Triangle(FPoint3 origin,  std::vector<FPoint3>relativePoints, RGBColor color, Material* material, CullMode state) :
    Primitive{ origin,color,material},
  
    m_CullMode{ state }
{
 
    FPoint3 Point = { m_Origin.x + relativePoints[0].x,m_Origin.y+ relativePoints[0].y, m_Origin.z + relativePoints[0].z };
     m_Vertices.push_back(Point);
     FPoint3 Point2 = { m_Origin.x + relativePoints[1].x,m_Origin.y + relativePoints[1].y, m_Origin.z + relativePoints[1].z };
     m_Vertices.push_back(Point2);
     FPoint3 Point3 = { m_Origin.x + relativePoints[2].x,m_Origin.y + relativePoints[2].y, m_Origin.z + relativePoints[2].z };
     m_Vertices.push_back(Point3);

     FVector3 a = m_Vertices[1] - m_Vertices[0];
     FVector3 b = m_Vertices[2] - m_Vertices[0];
     m_Normal = GetNormalized(Cross(a, b));
    
}

bool Triangle::Hit(const Ray& ray, HitRecord& hitrecord, bool isShadow) 
{
    return Hit(ray, hitrecord, isShadow, m_CullMode, m_Vertices, m_Normal);
}
bool Triangle::Hit(const Ray& ray, HitRecord& hitRecord, bool isShadowRay, const CullMode& cullmode, const std::vector<FPoint3>& vertices, const FVector3& normal)
{

    FVector3 a = vertices[1] - vertices[0];
    if (Dot(normal, ray.direction) == 0) return false;

    FVector3 L = vertices[0] - ray.origin;
    float t = Dot(L, normal) / Dot(ray.direction, normal);
    if (t < ray.tMin || t > ray.tMax) return false;
    FPoint3 Point = ray.origin + t * ray.direction;
    FVector3 edgeA = a;
    FVector3 pointToSide = Point - vertices[0];
    if (Dot(normal, Cross(edgeA, pointToSide)) < 0) return false;
    FVector3 edgeB = vertices[0] - vertices[2];
    FVector3 pointToSide1 = Point - vertices[2];
    if (Dot(normal, Cross(edgeB, pointToSide1)) < 0) return false;
    FVector3 edgeC = vertices[2] - vertices[1];
    FVector3 pointToSide2 = Point - vertices[2];
    if (Dot(normal, Cross(edgeC, pointToSide2)) < 0) return false;

    CullMode tempCull = cullmode;
    if (isShadowRay)
    {

        switch (tempCull)
        {
        case none:
            tempCull = CullMode::none;
            break;
        case frontFace:
            tempCull = CullMode::backFace;
            break;
        case backFace:
            tempCull = CullMode::frontFace;

            break;
        }
    }
    switch (tempCull)
    {
    case none:
        hitRecord.t = t;
        hitRecord.intersectionPoint = Point;
        hitRecord.normal = normal;
        hitRecord.color = RGBColor{};
        //hitRecord.m_pMaterial = m_pMaterial;
        return true;
        break;
    case frontFace:

        if (Dot(normal, ray.direction) < 0)
        {
            hitRecord.t = t;
            hitRecord.intersectionPoint = Point;
            hitRecord.normal = normal;
            hitRecord.color = RGBColor{};
          //  hitRecord.m_pMaterial = m_pMaterial;
            return true;
        }
        break;
    case backFace:
        if (Dot(normal, ray.direction) > 0)
        {
            hitRecord.t = t;
            hitRecord.intersectionPoint = Point;
            hitRecord.normal = normal;
            hitRecord.color = RGBColor{};
           // hitRecord.m_pMaterial = m_pMaterial;
            return true;
        }
        break;
    }
    return false;
}
CullMode Triangle::GetCullMode()const
{
    return m_CullMode;
}

void Triangle::SetCullMode(CullMode state)
{
    m_CullMode = state;
    
}



/*

    FVector3 a = m_Vertices[1] - m_Vertices[0];
    FVector3 b = m_Vertices[2] - m_Vertices[0];
    FVector3 normal = GetNormalized( Cross(a, b));
    if (Dot(normal, ray.direction) == 0) return false;

    FVector3 L = m_Vertices[0] - ray.origin;
    float t = Dot(L, normal) / Dot(ray.direction, normal);
    if (t < ray.tMin || t > ray.tMax) return false;
    FPoint3 Point = ray.origin + t * ray.direction;
    FVector3 edgeA = a;
    FVector3 pointToSide = Point -m_Vertices[0];
    if (Dot(normal, Cross(edgeA, pointToSide)) < 0) return false;
    FVector3 edgeB = m_Vertices[0] - m_Vertices[2];
    FVector3 pointToSide1 = Point - m_Vertices[2];
    if (Dot(normal, Cross(edgeB, pointToSide1)) < 0) return false;
    FVector3 edgeC = m_Vertices[2] - m_Vertices[1];
    FVector3 pointToSide2 = Point - m_Vertices[2];
    if (Dot(normal, Cross(edgeC, pointToSide2)) < 0) return false;

    CullMode tempCull = m_CullMode;
    if (isShadow)
    {

        switch (tempCull)
        {
        case none:
            tempCull = CullMode::none;
            break;
        case frontFace:
            tempCull = CullMode::backFace;
            break;
        case backFace:
            tempCull = CullMode::frontFace;

            break;
        }
    }
    switch (tempCull)
    {
    case none:
        hitrecord.t = t;
        hitrecord.intersectionPoint = Point;
        hitrecord.normal = normal;
        hitrecord.color = m_Color;
        hitrecord.m_pMaterial = m_pMaterial;
        return true;
        break;
    case frontFace:

        if (Dot(normal, ray.direction) < 0)
        {
            hitrecord.t = t;
            hitrecord.intersectionPoint = Point;
            hitrecord.normal = normal;
            hitrecord.color = m_Color;
            hitrecord.m_pMaterial = m_pMaterial;
            return true;
        }
        break;
    case backFace:
        if (Dot(normal, ray.direction) > 0)
        {
            hitrecord.t = t;
            hitrecord.intersectionPoint = Point;
            hitrecord.normal = normal;
            hitrecord.color = m_Color;
            hitrecord.m_pMaterial = m_pMaterial;
            return true;
        }
        break;
    }
    return false;*/