#pragma once
#include "Primitive.h"
#include <vector>
#include "Light.h"
#include "Material.h"
class SceneGraph final
{
public:

	static SceneGraph* GetInstance();
	static void Cleanup();

	void AddObjectsToGraph(Primitive* pObject);
	void AddLightsToGraph(Light* light);
	void AddMaterialsToGraph(Material* material);
	const std::vector<Primitive*>& GetObjects() const;
	const std::vector<Light*>& GetLights() const;
	~SceneGraph();
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) noexcept = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&&) noexcept = delete;
private:
	SceneGraph() = default;
	static SceneGraph* m_pInstance;

	std::vector<Primitive*> m_pObjects;
	std::vector<Light*> m_pLights;
	std::vector<Material*> m_pMaterials;
};

