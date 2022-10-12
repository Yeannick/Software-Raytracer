#pragma once
#include "Primitive.h"
#include <string>
#include "Triangle.h"
#include <fstream>
class TriangleMesh final : public Primitive
{
public:	
	TriangleMesh(const Elite::FPoint3& Origin, Material* material, const std::string& filename);
	~TriangleMesh() = default;
    TriangleMesh(const TriangleMesh&) = delete;
    TriangleMesh(TriangleMesh&&) noexcept = delete;
    TriangleMesh& operator=(const TriangleMesh&) = delete;
    TriangleMesh& operator=(TriangleMesh&&) noexcept = delete;
	virtual bool Hit(const Ray& ray, HitRecord& hitrecord, bool isShadow)  override; 
   
private:

    void CreateTriangles();
    void Parse(const std::string& fileName);

    std::vector<Triangle*> m_pTriangles;
    std::vector<FPoint3> m_VertexBuffer;
    /*{ {-.75f, 1.5f, 0.0f}, {-.75f, 0.f, 0.f}, {.75f, 0.f, 0.f}, {.75f, 1.5f,1.0f} }*/
    std::vector<unsigned int> m_IndexBuffer;
        /*{0, 1, 2, 0, 2, 3}*/
};

