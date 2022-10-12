#pragma once
#include "EMath.h"
class PerspectiveCamera final
{
public:

	static PerspectiveCamera* GetInstance();
	static void Cleanup();
	~PerspectiveCamera();

	PerspectiveCamera(const PerspectiveCamera&) = delete;
	PerspectiveCamera(PerspectiveCamera&&) noexcept = delete;
	PerspectiveCamera& operator=(const PerspectiveCamera&) = delete;
	PerspectiveCamera& operator=(PerspectiveCamera&&) noexcept = delete;

	static void SetCamera(float screenWidth, float screenHeight, float degrees, const Elite::FPoint3& worldposition);
	void CalculateMatrix(const Elite::FVector3& forward);

	void Update(float deltaTime);

	
	Elite::FPoint3 TranslatePosition(const Elite::FPoint3& point);
	void Rotate(float yaw, float pitch);
	float GetAspectRatio() const;
	float GetFov() const;
	Elite::FPoint3 GetPosition() const;

private:

	PerspectiveCamera();
	PerspectiveCamera(float screenwidth, float screenheight, float degrees, Elite::FPoint3 worldposition);

	// camera datamembers
	static PerspectiveCamera* m_pInstance;
	float m_AspectRatio{};
	float m_Fov{};
	Elite::FMatrix4 m_LookAtMatrix{};

	// mouse speeds 
	float m_MouseHorSpeed = 1.f, m_MouseVertSpeed = 1.f, m_MouseRotSpeed = 0.25f;
	float m_MouseForwardSpeed{ 4.f };
};

