#include "PerspectiveCamera.h"
#include "SDL.h"
#include <iostream>

PerspectiveCamera* PerspectiveCamera::m_pInstance{};

PerspectiveCamera* PerspectiveCamera::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new PerspectiveCamera{};
	}
	return m_pInstance;
}
void PerspectiveCamera::Cleanup()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}
PerspectiveCamera::PerspectiveCamera()
{

}
PerspectiveCamera::PerspectiveCamera(float screenWidth, float screenHeight, float degrees, Elite::FPoint3 worldPosition) :
	m_AspectRatio{screenWidth/screenHeight},
	m_Fov{ float(tan(Elite::ToRadians(degrees) / 2)) },
	m_LookAtMatrix{Elite::FMatrix4::Identity()}
{
	m_LookAtMatrix[3].xyz = Elite::FVector3{ worldPosition };
}

PerspectiveCamera::~PerspectiveCamera()
{
	/*delete m_pInstance;
	m_pInstance = nullptr;*/
}

void PerspectiveCamera::SetCamera(float screenWidth, float screenHeight, float degrees, const Elite::FPoint3& worldposition)
{
	delete m_pInstance;

	m_pInstance = new PerspectiveCamera{ screenWidth , screenHeight , degrees , worldposition };
}
void PerspectiveCamera::CalculateMatrix(const Elite::FVector3& forward)
{
	m_LookAtMatrix[2].xyz = Elite::GetNormalized(forward);
	m_LookAtMatrix[0].xyz = Elite::GetNormalized(Elite::Cross(Elite::FVector3{ 0.f, 1.f, 0.f }, m_LookAtMatrix[2].xyz));
	m_LookAtMatrix[1].xyz = Elite::GetNormalized(Elite::Cross(m_LookAtMatrix[2].xyz, m_LookAtMatrix[0].xyz));
}

void PerspectiveCamera::Update(float deltaTime)
{
	int x, y;

	uint32_t state = SDL_GetRelativeMouseState(&x, &y);
	const Uint8* keyboardstate = SDL_GetKeyboardState(NULL);
	Elite::FVector2 mouseMovement{ float(x) , float(-y) };
	//SDL_PumpEvents();

	if (state & SDL_BUTTON_LMASK && state & SDL_BUTTON_RMASK)
	{
		Elite::FVector3 worldUp{ 0.f,1.f,0.f };
		Elite::FVector3 right{ m_LookAtMatrix[0].xyz };
		Elite::FVector3 movement{ worldUp * m_MouseVertSpeed * deltaTime * mouseMovement.y + right * m_MouseHorSpeed * deltaTime * mouseMovement.x };
		m_LookAtMatrix[3].xyz += movement;

	}
	else if (state & SDL_BUTTON_LMASK)
	{
		Elite::FVector3 forward{ m_LookAtMatrix[2].xyz };
		Elite::FVector3 movement{ forward * m_MouseForwardSpeed * deltaTime * mouseMovement.y };
		m_LookAtMatrix[3].xyz += movement;
		Rotate(m_MouseRotSpeed * deltaTime * mouseMovement.x, 0);
	}
	else if (state & SDL_BUTTON_RMASK)
	{

		Rotate(m_MouseRotSpeed * deltaTime * mouseMovement.x, m_MouseRotSpeed * deltaTime * mouseMovement.y);
	}
	else if(keyboardstate[SDL_SCANCODE_W])
	{
		Elite::FVector3 forward{ m_LookAtMatrix[2].xyz };
		Elite::FVector3 movement{ -forward * deltaTime };
		m_LookAtMatrix[3].xyz += movement;
	}
	else if (keyboardstate[SDL_SCANCODE_S])
	{
		Elite::FVector3 forward{ m_LookAtMatrix[2].xyz };
		Elite::FVector3 movement{ forward * deltaTime };
		m_LookAtMatrix[3].xyz += movement;
	}
	else if (keyboardstate[SDL_SCANCODE_A])
	{
		Elite::FVector3 Right{ m_LookAtMatrix[0].xyz };
		Elite::FVector3 movement{ -Right * deltaTime };
		m_LookAtMatrix[3].xyz += movement;
	}
	else if (keyboardstate[SDL_SCANCODE_D])
	{
		Elite::FVector3 Right{ m_LookAtMatrix[0].xyz };
		Elite::FVector3 movement{ Right * deltaTime };
		m_LookAtMatrix[3].xyz += movement;
	}

}



Elite::FPoint3 PerspectiveCamera::TranslatePosition(const Elite::FPoint3& point)
{
	Elite::FPoint4 pos{ point };

	return (m_LookAtMatrix * pos).xyz;
}
void PerspectiveCamera::Rotate(float yaw, float pitch)
{
	Elite::FVector3 forward{ m_LookAtMatrix[2].xyz };
	Elite::FVector3 right{ m_LookAtMatrix[0].xyz };

	Elite::FMatrix3 yawRotation{ Elite::MakeRotationY(yaw) };

	Elite::FMatrix3 pitchRotation{ Elite::MakeRotation(pitch, right) };

	forward = yawRotation * forward;
	forward = pitchRotation * forward;

	CalculateMatrix(forward);
}


float PerspectiveCamera::GetAspectRatio() const
{
	return m_AspectRatio;
}

float PerspectiveCamera::GetFov() const
{
	return m_Fov;
}
Elite::FPoint3 PerspectiveCamera::GetPosition() const
{
	return Elite::FPoint3(m_LookAtMatrix[3].xyz);
}