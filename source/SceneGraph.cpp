#include "SceneGraph.h"
SceneGraph* SceneGraph::m_pInstance{};

SceneGraph* SceneGraph::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SceneGraph();

	}
	return m_pInstance;
}

void SceneGraph::Cleanup()
{
	
	delete m_pInstance;
	m_pInstance = nullptr;
}

void SceneGraph::AddObjectsToGraph(Primitive* pObject)
{
	m_pObjects.push_back(pObject);
}

void SceneGraph::AddLightsToGraph(Light* light)
{
	m_pLights.push_back(light);
}

void SceneGraph::AddMaterialsToGraph(Material* material)
{
	m_pMaterials.push_back(material);
}

const std::vector<Primitive*>& SceneGraph::GetObjects() const
{
	return m_pObjects;
}

const std::vector<Light*>& SceneGraph::GetLights() const
{
	return m_pLights;
}

SceneGraph::~SceneGraph()
{
	for (auto pObject : m_pObjects)
	{
		delete pObject;
	}
	m_pObjects.clear();
	for (auto pLight : m_pLights)
	{
		delete pLight;
	}
	m_pLights.clear();
	for (auto pMaterial: m_pMaterials)
	{
		delete pMaterial;
	}
	m_pMaterials.clear();
}