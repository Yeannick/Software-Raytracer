#include "TriangleMesh.h"
#include <iostream>
#include <sstream>


TriangleMesh::TriangleMesh(const Elite::FPoint3& Origin, Material* material, const std::string& filename):
	Primitive{ Origin,{}, material }
	
{
	Parse(filename);
	//CreateTriangles();
	/*for (int i{}; i < m_VertexBuffer.size(); i++)
	{
		std::cout << m_VertexBuffer[i].x << " " << m_VertexBuffer[i].y << " " << m_VertexBuffer[i].z << std::endl;
	}*/
}

bool TriangleMesh::Hit(const Ray& ray, HitRecord& hitrecord, bool isShadow)
{
	for (int i{ 0 }; i < m_IndexBuffer.size() / 3.f; i++)
	{
		unsigned int firstIndex{ m_IndexBuffer[(i * 3) + 0] };
		unsigned int secondIndex{ m_IndexBuffer[(i * 3) + 1] };
		unsigned int thirdIndex{ m_IndexBuffer[(i * 3) + 2] };
		std::vector<FPoint3> tempVertices{ FPoint3(FVector3(m_Origin) + FVector3(m_VertexBuffer[firstIndex - 1])), FPoint3(FVector3(m_Origin) + FVector3(m_VertexBuffer[secondIndex - 1])), FPoint3(FVector3(m_Origin) + FVector3(m_VertexBuffer[thirdIndex - 1])) };
		FVector3 a{ tempVertices[1] - tempVertices[0] };
		FVector3 b{ tempVertices[2] - tempVertices[0] };

		FVector3 normal = Cross(a, b);
		Normalize(normal);
		if (Triangle::Hit(ray, hitrecord, isShadow, CullMode::frontFace, tempVertices, normal))
		{
			hitrecord.m_pMaterial = m_pMaterial;
			return true;
		}
			
	}
	return false;
	/*for (Triangle* pTriangle : m_pTriangles)
	{
		if (pTriangle->Hit(ray, hitrecord, isShadow))
			return true;
	}
	return false;*/
}

//void TriangleMesh::CreateTriangles()
//{
//	std::vector<FPoint3> vertices{};
//	for ( int i = 0; i < m_IndexBuffer.size(); i++)
//	{
//		vertices.push_back(m_VertexBuffer[m_IndexBuffer[i] - 1]);
//		if (vertices.size()==3)
//		{
//			Triangle* triangle = new Triangle { m_Origin,vertices,{},m_pMaterial,CullMode::frontFace };
//			m_pTriangles.push_back(triangle);
//			
//			vertices.clear();
//			//std::cout << std::endl;
//		}
//		
//	}
//}

void TriangleMesh::Parse(const std::string& fileName)
{
	std::ifstream Reader(fileName, std::ios::in);
	if (!Reader)
	{
		std::cout << "couldnt open : " << fileName << std::endl;
	}
	std::string line;
	while (std::getline(Reader,line))
	{
		// check for vertex
		if (line.substr(0,2) == "v ")
		{
			std::istringstream v (line.substr(2));
			FPoint3 Vertex;
			float x, y, z;
			v >> x;
			v >> y;
			v >> z;
			Vertex.x = x;
			Vertex.y = y;
			Vertex.z = z;

			m_VertexBuffer.push_back(Vertex);
		}
		// check for Faces
		else if (line.substr(0,2) == "f ")
		{
			std::istringstream f(line.substr(2));
			unsigned int x, y, z;
			f >> x;
			f >> y;
			f >> z;
			m_IndexBuffer.push_back(x);
			m_IndexBuffer.push_back(y);
			m_IndexBuffer.push_back(z);
		}
	}
}
